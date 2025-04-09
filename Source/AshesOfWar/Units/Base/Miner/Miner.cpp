#include "Miner.h"
#include "AshesOfWar/AI/AIControllers/UnitAIController.h"
#include "AshesOfWar/AI/StateTree/UnitStateTreeAIComponent.h"
#include "AshesOfWar/Resources/Management/UResourceComponent.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"
#include "StateTree.h"

AMiner::AMiner()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the resource component (not attached to scene hierarchy)
	ResourceComponent = CreateDefaultSubobject<UResourceComponent>(TEXT("ResourceComponent"));
}

void AMiner::OnBeginPlay_Implementation()
{
	Super::OnBeginPlay_Implementation();

	AUnitAIController* AIController = GetAIController();
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("[Miner] Missing AIController"));
		return;
	}

	UUnitStateTreeAIComponent* StateTreeAIComponent = AIController->GetUnitStateTreeAIComponent();
	if (!StateTreeAIComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("[Miner] Missing StateTreeAIComponent"));
		return;
	}

	if (!MinerStateTreeAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("[Miner] No StateTree asset assigned"));
		return;
	}

	// Log important for debugging StateTree assignment
	UE_LOG(LogTemp, Log, TEXT("[Miner] Assigned StateTree: %s"), *MinerStateTreeAsset->GetName());

	// Assign and start StateTree AI logic
	StateTreeAIComponent->SetStateTree(MinerStateTreeAsset);
	StateTreeAIComponent->StartLogic();

	UE_LOG(LogTemp, Log, TEXT("[Miner] StateTree AI logic successfully started"));
}

void AMiner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ResourceComponent) return;

	// Automatically start mining when close enough to the resource node
	AAResourceNode* Resource = ResourceComponent->GetCurrentResourceNode();
	if (Resource && FVector::Dist(GetActorLocation(), Resource->GetActorLocation()) < 150.f)
	{
		if (!ResourceComponent->IsCollecting())
		{
			MineResource();
		}
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
