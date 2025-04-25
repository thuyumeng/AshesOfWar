#include "Miner.h"
#include "AshesOfWar/AI/AIControllers/UnitAIController.h"
#include "AshesOfWar/AI/StateTree/UnitStateTreeAIComponent.h"
#include "AshesOfWar/Resources/Management/UResourceComponent.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"
#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"
#include "AshesOfWar/Core/GameStates/ARTSGameState.h"
#include "EngineUtils.h"
#include "AshesOfWar/Buildings/Base/EBuildingType.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

AMiner::AMiner()
{
	PrimaryActorTick.bCanEverTick = true;
	ResourceComponent = CreateDefaultSubobject<UResourceComponent>(TEXT("ResourceComponent"));
}

void AMiner::OnBeginPlay_Implementation()
{
	Super::OnBeginPlay_Implementation();

	if (!OwningPlayerState)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC && PC->PlayerState)
		{
			SetOwningPlayerState(PC->PlayerState);
		}
	}

	if (AUnitAIController* AIController = GetAIController())
	{
		if (UUnitStateTreeAIComponent* StateTreeAIComponent = AIController->GetUnitStateTreeAIComponent())
		{
			if (MinerStateTreeAsset)
			{
				StateTreeAIComponent->SetStateTree(MinerStateTreeAsset);
				StateTreeAIComponent->StartLogic();
			}
		}
	}
}

void AMiner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDepositing)
		HandleDepositing(DeltaTime);
	else
		HandleMining(DeltaTime);
}

void AMiner::HandleMining(float DeltaTime)
{
	if (!ResourceComponent) return;

	AAResourceNode* Resource = ResourceComponent->GetCurrentResourceNode();
	if (!Resource || Resource->GetQteDisponible() <= 0)
	{
		StopMining();
		ResourceComponent->SetCurrentResourceNode(nullptr);

		// Affichage du log d'erreur une fois toutes les 5 secondes
		static float EmptyNodeLogTimer = 0.f;
		EmptyNodeLogTimer += DeltaTime;

		if (EmptyNodeLogTimer >= 5.f)
		{
			UE_LOG(LogTemp, Error, TEXT("❗ Le node est vide, minage arrêté."));
			EmptyNodeLogTimer = 0.f;
		}

		return;
	}

	if (FVector::Dist(GetActorLocation(), Resource->GetActorLocation()) <= MiningDistanceThreshold)
	{
		static float RemainingLogAccumulator = 0.f;
		RemainingLogAccumulator += DeltaTime;

		if (RemainingLogAccumulator >= 1.f)
		{
			UE_LOG(LogTemp, Warning, TEXT("[⛏️ Node Stat] Ressource restante : %d unités (%s)"),
				Resource->GetQteDisponible(),
				*UEnum::GetValueAsString(Resource->GetResourceType()));

			RemainingLogAccumulator = 0.f;
		}
		CarriedResourceType = Resource->GetResourceType();

		// Accumule la quantité potentielle à extraire
		ResourceAccumulator += CollectionRatePerSecond * DeltaTime;

		// Extraction quand une unité pleine est atteinte
		int32 UnitsToExtract = FMath::FloorToInt(ResourceAccumulator);
		if (UnitsToExtract > 0)
		{
			int32 Available = Resource->GetQteDisponible();
			int32 ActualExtracted = FMath::Min(Available, UnitsToExtract);

			CarriedAmount += ActualExtracted;
			CarriedAmount = FMath::Clamp(CarriedAmount, 0.f, static_cast<float>(CarriedCapacity));
			Resource->SetQteDisponible(Available - ActualExtracted);

			ResourceAccumulator -= ActualExtracted;

			// Accumulation pour limiter les logs à 1 seconde
			static float LogTimeAccumulator = 0.f;
			LogTimeAccumulator += DeltaTime;
			if (LogTimeAccumulator >= 1.f)
			{
				UE_LOG(LogTemp, Warning, TEXT("[⛏️ Minage Tick] -%d récolté | Node: %d restant | Transporté: %.2f / %d"),
					ActualExtracted,
					Resource->GetQteDisponible(),
					CarriedAmount,
					CarriedCapacity);
				LogTimeAccumulator = 0.f;
			}
		}

		// Si plein, on passe au dépôt
		if (CarriedAmount >= CarriedCapacity)
		{
			bIsDepositing = true;
			FindNearestHQBase();
			MoveToDeposit();
			UE_LOG(LogTemp, Warning, TEXT("📦 Capacité atteinte. Début du dépôt..."));
		}
	}
	else
	{
		MoveToLocation(Resource->GetActorLocation());
	}
}



void AMiner::HandleDepositing(float DeltaTime)
{
	if (!CurrentDepositBaseTarget)
	{
		FindNearestHQBase();
		if (!CurrentDepositBaseTarget) return;
	}

	if (FVector::Dist(GetActorLocation(), CurrentDepositBaseTarget->GetActorLocation()) <= DepositDistanceThreshold)
	{
		DepositAtBase();
	}
	else
	{
		MoveToLocation(CurrentDepositBaseTarget->GetActorLocation());
	}
}

void AMiner::MoveToDeposit()
{
	if (CurrentDepositBaseTarget)
	{
		MoveToLocation(CurrentDepositBaseTarget->GetActorLocation());
	}
}

void AMiner::DepositAtBase()
{
	if (CarriedAmount <= 0 || !CurrentDepositBaseTarget)
	{
		if (CarriedAmount > 0 && ResourceComponent && ResourceComponent->GetCurrentResourceNode())
		{
			int NodeRemaining = ResourceComponent->GetCurrentResourceNode()->GetQteDisponible();
			if (NodeRemaining <= 0)
			{
				UE_LOG(LogTemp, Error, TEXT("🚨 Le mineur transporte %.2f %s alors que le node est VIDE."),
					CarriedAmount,
					*UEnum::GetValueAsString(CarriedResourceType));
			}
		}
		return;
	} 

	if (AARTSGameState* GameState = GetWorld()->GetGameState<AARTSGameState>())
	{
		if (APlayerState* MyPlayerState = GetOwningPlayerState())
		{
			GameState->AddResource(MyPlayerState, CarriedResourceType, static_cast<int32>(CarriedAmount));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("❌ DepositAtBase: OwningPlayerState is null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("❌ DepositAtBase: GameState not found"));
	}

	// Plus besoin de retirer les ressources du node ici, ça a déjà été fait dans BeginCollection()

	CarriedAmount = 0;
	bIsDepositing = false;
}


void AMiner::FindNearestHQBase()
{
	if (AARTSGameState* GameState = GetWorld()->GetGameState<AARTSGameState>())
	{
		float MinDistance = TNumericLimits<float>::Max();
		ABaseBuilding* BestBase = nullptr;

		for (TActorIterator<ABaseBuilding> It(GetWorld()); It; ++It)
		{
			ABaseBuilding* Base = *It;
			if (!Base) continue;

			if (Base->BuildingData.BuildingType == EBuildingType::HQ)
			{
				float Distance = FVector::Dist(GetActorLocation(), Base->GetActorLocation());
				if (Distance < MinDistance)
				{
					MinDistance = Distance;
					BestBase = Base;
				}
			}
		}

		CurrentDepositBaseTarget = BestBase;
	}
}

void AMiner::MoveToLocation(const FVector& Destination)
{
	if (AUnitAIController* AIController = Cast<AUnitAIController>(GetController()))
	{
		const float MinerAcceptanceRadius = 120.f;

		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalLocation(Destination);
		MoveRequest.SetAcceptanceRadius(MinerAcceptanceRadius);

		FNavPathSharedPtr NavPath;
		AIController->MoveTo(MoveRequest, &NavPath);
	}
}

void AMiner::MineResource()
{
	if (ResourceComponent)
	{
		AAResourceNode* Node = ResourceComponent->GetCurrentResourceNode();

		// Vérifie que le node est valide et contient des ressources
		if (!Node)
		{
			UE_LOG(LogTemp, Error, TEXT("❗ MineResource() : Aucun node assigné. Minage annulé."));
			return;
		}

		if (Node->GetQteDisponible() <= 0)
		{
			UE_LOG(LogTemp, Error, TEXT("❗ MineResource() : Node %s est vide (%d unités). Minage bloqué."),
				*Node->GetName(),
				Node->GetQteDisponible());
			return;
		}

		// Lancement de la collecte
		ResourceComponent->BeginCollection();
	}
}


void AMiner::StopMining()
{
	if (ResourceComponent)
	{
		ResourceComponent->StopCollection();
	}
}

void AMiner::DepositCollectedResources()
{
	if (ResourceComponent)
	{
		ResourceComponent->DepositResources();
	}
}

void AMiner::SetCurrentResourceNode(AAResourceNode* NewNode)
{
	if (ResourceComponent)
	{
		ResourceComponent->SetCurrentResourceNode(NewNode);
	}
}

UResourceComponent* AMiner::GetResourceComponent() const
{
	return ResourceComponent;
}

void AMiner::AddConstructionTarget(AActor* Building)
{
	if (Building && !ActiveConstructionTargets.Contains(Building))
	{
		ActiveConstructionTargets.Add(Building);
	}
}

void AMiner::RemoveConstructionTarget(AActor* Building)
{
	if (Building)
	{
		ActiveConstructionTargets.Remove(Building);
	}
}

bool AMiner::IsConstructing() const
{
	return ActiveConstructionTargets.Num() > 0;
}

bool AMiner::IsDepositing() const
{
	return bIsDepositing;
}

AActor* AMiner::GetCurrentDepositTarget() const
{
	return CurrentDepositBaseTarget;
}

AActor* AMiner::GetCurrentResourceTarget() const
{
	return ResourceComponent ? Cast<AActor>(ResourceComponent->GetCurrentResourceNode()) : nullptr;
}

void AMiner::SetOwningPlayerState(APlayerState* Player)
{
	OwningPlayerState = Player;
	UE_LOG(LogTemp, Warning, TEXT("✅ OwningPlayerState défini : %s"), Player ? *Player->GetName() : TEXT("nullptr"));
}

APlayerState* AMiner::GetOwningPlayerState() const
{
	return OwningPlayerState;
}
