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
		return;
	}

	if (FVector::Dist(GetActorLocation(), Resource->GetActorLocation()) <= MiningDistanceThreshold)
	{
		CarriedResourceType = Resource->GetResourceType();
		CarriedAmount += CollectionRatePerSecond * DeltaTime;
		CarriedAmount = FMath::Clamp(CarriedAmount, 0.f, static_cast<float>(CarriedCapacity));

		if (CarriedAmount >= CarriedCapacity)
		{
			bIsDepositing = true;
			FindNearestHQBase();
			MoveToDeposit();
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
	if (CarriedAmount <= 0 || !CurrentDepositBaseTarget) return;

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

	if (ResourceComponent)
	{
		if (AAResourceNode* ResourceNode = ResourceComponent->GetCurrentResourceNode())
		{
			ResourceNode->ConsumeResource(CarriedAmount);
		}
	}

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
