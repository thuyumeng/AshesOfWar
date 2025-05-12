#include "Miner.h"
#include "AshesOfWar/AI/AIControllers/UnitAIController.h"
#include "AshesOfWar/Resources/Management/UResourceComponent.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"
#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"
#include "AshesOfWar/GameplayTags/AI/AIEventTags.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

// -------------------- Constructor --------------------
AMiner::AMiner()
{
	PrimaryActorTick.bCanEverTick = false;
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

	// Switch to the AIControlled State
	SwitchToState(TEXT("AIControlled"));
}

// -------------------- Deposit Logic -------------------

void AMiner::DepositAtBase()
{
	if (ResourceComponent)
	{
		ResourceComponent->DepositResources();
	}
}

// -------------------- Resource Commands --------------------
void AMiner::MineResource()
{
	if (!ResourceComponent) return;
	AAResourceNode* Node = ResourceComponent->GetCurrentResourceNode();
	if (!Node || Node->GetQteDisponible() <= 0) return;
	ResourceComponent->BeginCollection();
	SwitchToState(TEXT("AIControlled"));
}

void AMiner::StopMining()
{
	if (ResourceComponent) ResourceComponent->StopCollection();
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

// -------------------- Init the AttributeSets--------------------
void AMiner::InitAttributeSets()
{
	this->InitAttributeSetsByCurveTables(TEXT("Miner"));
}

// -------------------- Accessors --------------------
AActor* AMiner::GetCurrentDepositTarget() const
{
	return ResourceComponent ? Cast<AActor> (ResourceComponent->GetDepositBaseTarget()) :nullptr;
}

AActor* AMiner::GetCurrentResourceTarget() const
{
	return ResourceComponent ? Cast<AActor>(ResourceComponent->GetCurrentResourceNode()) : nullptr;
}