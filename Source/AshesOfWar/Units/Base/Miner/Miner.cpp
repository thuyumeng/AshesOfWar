#include "Miner.h"
#include "AshesOfWar/AI/AIControllers/UnitAIController.h"
#include "AshesOfWar/AI/StateTree/UnitStateTreeAIComponent.h"
#include "AshesOfWar/Resources/Management/UResourceComponent.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"
#include "StateTree.h"

AMiner::AMiner()
{
	PrimaryActorTick.bCanEverTick = true;

	// Création du composant de ressource (non attaché à la hiérarchie de scène)
	ResourceComponent = CreateDefaultSubobject<UResourceComponent>(TEXT("ResourceComponent"));
}

void AMiner::OnBeginPlay_Implementation()
{
	Super::OnBeginPlay_Implementation();

	UE_LOG(LogTemp, Warning, TEXT("[Miner] Début de OnBeginPlay_Implementation"));

	AUnitAIController* AIController = GetAIController();
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("[Miner] AIController est null"));
		return;
	}

	UUnitStateTreeAIComponent* StateTreeAIComponent = AIController->GetUnitStateTreeAIComponent();
	if (!StateTreeAIComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("[Miner] StateTreeAIComponent est null"));
		return;
	}

	if (!MinerStateTreeAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("[Miner] StateTree est null (non assigné dans le BP)"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("[Miner] StateTree assigné : %s"), *MinerStateTreeAsset->GetName());

	StateTreeAIComponent->SetStateTree(MinerStateTreeAsset);
	StateTreeAIComponent->StartLogic();

	UE_LOG(LogTemp, Log, TEXT("[Miner] IA StateTree démarrée avec succès"));
}


void AMiner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ResourceComponent) return;

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
