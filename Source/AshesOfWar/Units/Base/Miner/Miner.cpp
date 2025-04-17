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

AMiner::AMiner()
{
	PrimaryActorTick.bCanEverTick = true;

	ResourceComponent = CreateDefaultSubobject<UResourceComponent>(TEXT("ResourceComponent"));
}

void AMiner::OnBeginPlay_Implementation()
{
	Super::OnBeginPlay_Implementation();

	AUnitAIController* AIController = GetAIController();
	if (AIController)
	{
		UUnitStateTreeAIComponent* StateTreeAIComponent = AIController->GetUnitStateTreeAIComponent();
		if (StateTreeAIComponent && MinerStateTreeAsset)
		{
			StateTreeAIComponent->SetStateTree(MinerStateTreeAsset);
			StateTreeAIComponent->StartLogic();
		}
	}
}

void AMiner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDepositing)
	{
		HandleDepositing(DeltaTime);
	}
	else
	{
		HandleMining(DeltaTime);
	}
}

// --- Mining Logic ---

void AMiner::HandleMining(float DeltaTime)
{
	if (!ResourceComponent) return;

	AAResourceNode* Resource = ResourceComponent->GetCurrentResourceNode();
	if (!Resource) return;

	if (Resource->GetQteDisponible() <= 0)
	{
		StopMining();
		ResourceComponent->SetCurrentResourceNode(nullptr);
		return;
	}

	if (FVector::Dist(GetActorLocation(), Resource->GetActorLocation()) <= MiningDistanceThreshold)
	{
		CarriedResourceType = Resource->GetResourceType();
		CarriedAmount += CollectionRatePerSecond * DeltaTime;
		CarriedAmount = FMath::Clamp(CarriedAmount, 0, CarriedCapacity);

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
	if (CarriedAmount <= 0 || !CurrentDepositBaseTarget)
	{
		return;
	}

	AARTSGameState* GameState = GetWorld()->GetGameState<AARTSGameState>();
	if (GameState)
	{
		APlayerState* MyPlayerState = GetPlayerState<APlayerState>();
		if (MyPlayerState)
		{
			GameState->AddResource(MyPlayerState, CarriedResourceType, CarriedAmount);
		}
	}

	CarriedAmount = 0;
	bIsDepositing = false;
}

void AMiner::FindNearestHQBase()
{
	AARTSGameState* GameState = GetWorld()->GetGameState<AARTSGameState>();
	if (!GameState) return;

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

// --- Movement Logic ---

void AMiner::MoveToLocation(const FVector& Destination)
{
	AUnitAIController* AIController = Cast<AUnitAIController>(GetController());
	if (AIController)
	{
		AIController->MoveToLocation(Destination, 10.f);
	}
}

// --- Resource Interface ---

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

// --- Construction Interface ---

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

// --- Query Status ---

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
