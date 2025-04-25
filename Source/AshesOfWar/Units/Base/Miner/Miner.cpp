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

// -------------------- Constructor --------------------
AMiner::AMiner()
{
	PrimaryActorTick.bCanEverTick = true;
	ResourceComponent = CreateDefaultSubobject<UResourceComponent>(TEXT("ResourceComponent"));
}

// -------------------- Lifecycle --------------------
void AMiner::OnBeginPlay_Implementation()
{
	Super::OnBeginPlay_Implementation();

	if (!OwningPlayerState)
	{
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
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
	if (bIsDepositing) HandleDepositing(DeltaTime);
	else HandleMining(DeltaTime);
}

// -------------------- Mining Logic --------------------
void AMiner::HandleMining(float DeltaTime)
{
	if (!ResourceComponent) return;

	AAResourceNode* Resource = ResourceComponent->GetCurrentResourceNode();

	if (!Resource || Resource->GetQteDisponible() <= 0)
	{
		FVector SearchOrigin = Resource ? Resource->GetActorLocation() : GetActorLocation();
		AAResourceNode* NearestValidNode = nullptr;
		float NearestDist = 450.f;

		for (TActorIterator<AAResourceNode> It(GetWorld()); It; ++It)
		{
			AAResourceNode* OtherNode = *It;
			if (OtherNode && OtherNode->GetQteDisponible() > 0 && OtherNode != Resource)
			{
				float Distance = FVector::Dist(SearchOrigin, OtherNode->GetActorLocation());
				if (Distance <= NearestDist)
				{
					NearestValidNode = OtherNode;
					NearestDist = Distance;
				}
			}
		}

		if (NearestValidNode)
		{
			SetCurrentResourceNode(NearestValidNode);
			MineResource();
			return;
		}

		StopMining();
		ResourceComponent->SetCurrentResourceNode(nullptr);
		static float EmptyNodeLogTimer = 0.f;
		EmptyNodeLogTimer += DeltaTime;
		if (!bNodeReportedEmpty && EmptyNodeLogTimer >= 5.f)
		{
			EmptyNodeLogTimer = 0.f;
			bNodeReportedEmpty = true;
		}
		return;
	}

	if (FVector::Dist(GetActorLocation(), Resource->GetActorLocation()) <= MiningDistanceThreshold)
	{
		bNodeReportedEmpty = false;
		CarriedResourceType = Resource->GetResourceType();
		ResourceAccumulator += CollectionRatePerSecond * DeltaTime;
		int32 UnitsToExtract = FMath::FloorToInt(ResourceAccumulator);
		if (UnitsToExtract > 0)
		{
			int32 Available = Resource->GetQteDisponible();
			int32 ActualExtracted = FMath::Min(Available, UnitsToExtract);
			CarriedAmount += ActualExtracted;
			CarriedAmount = FMath::Clamp(CarriedAmount, 0.f, static_cast<float>(CarriedCapacity));
			Resource->SetQteDisponible(Available - ActualExtracted);
			ResourceAccumulator -= ActualExtracted;
		}

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

// -------------------- Deposit Logic --------------------
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
	}
	CarriedAmount = 0;
	bIsDepositing = false;
}

// -------------------- Resource Commands --------------------
void AMiner::MineResource()
{
	if (!ResourceComponent) return;
	AAResourceNode* Node = ResourceComponent->GetCurrentResourceNode();
	if (!Node || Node->GetQteDisponible() <= 0) return;
	ResourceComponent->BeginCollection();
}

void AMiner::StopMining()
{
	if (ResourceComponent) ResourceComponent->StopCollection();
}

void AMiner::DepositCollectedResources()
{
	if (ResourceComponent) ResourceComponent->DepositResources();
}

void AMiner::SetCurrentResourceNode(AAResourceNode* NewNode)
{
	if (ResourceComponent) ResourceComponent->SetCurrentResourceNode(NewNode);
}

UResourceComponent* AMiner::GetResourceComponent() const
{
	return ResourceComponent;
}

// -------------------- Construction --------------------
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

// -------------------- Ownership --------------------
void AMiner::SetOwningPlayerState(APlayerState* Player)
{
	OwningPlayerState = Player;
}

APlayerState* AMiner::GetOwningPlayerState() const
{
	return OwningPlayerState;
}

// -------------------- Movement --------------------
void AMiner::MoveToLocation(const FVector& Destination)
{
	if (AUnitAIController* AIController = Cast<AUnitAIController>(GetController()))
	{
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalLocation(Destination);
		MoveRequest.SetAcceptanceRadius(120.f);
		FNavPathSharedPtr NavPath;
		AIController->MoveTo(MoveRequest, &NavPath);
	}
}

// -------------------- Find Deposit Location --------------------
void AMiner::FindNearestHQBase()
{
	//if (AARTSGameState* GameState = GetWorld()->GetGameState<AARTSGameState>())
	//{
		float MinDistance = TNumericLimits<float>::Max();
		ABaseBuilding* BestBase = nullptr;
		for (TActorIterator<ABaseBuilding> It(GetWorld()); It; ++It)
		{
			ABaseBuilding* Base = *It;
			if (!Base || Base->BuildingData.BuildingType != EBuildingType::HQ) continue;
			float Distance = FVector::Dist(GetActorLocation(), Base->GetActorLocation());
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				BestBase = Base;
			}
		}
		CurrentDepositBaseTarget = BestBase;
	//}
}

// -------------------- Accessors --------------------
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
