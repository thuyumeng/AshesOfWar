#include "UResourceComponent.h"

#include "AshesOfWar/AI/StateTree/UnitStateTreeAIComponent.h"
#include "AshesOfWar/Core/GameStates/ARTSGameState.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"
#include "AshesOfWar/GameplayTags/AI/AIEventTags.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"
#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Pawn.h"

// -------------------- Constructor --------------------
UResourceComponent::UResourceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	bIsCollecting = false;
	CarriedAmount = 0;
	CarriedMaxCapacity = 50;
	CarriedResourceType = EResourceType::Aetherium;
	CurrentResourceNode = nullptr;
}

// -------------------- Collection --------------------
void UResourceComponent::BeginCollection()
{
	if (!CurrentResourceNode.IsValid()) return;

	CarriedResourceType = CurrentResourceNode->GetResourceType();

	const int32 Available = CurrentResourceNode->GetQteDisponible();
	const int32 ExtractionRate = CurrentResourceNode->GetExtRate();

	if (Available <= 0 || ExtractionRate <= 0) return;

	bIsCollecting = true;
}

void UResourceComponent::StopAndTriggerEmptyEvent()
{
	StopCollection();
	AActor* Owner = GetOwner();

	UUnitStateTreeAIComponent* StateTreeAIComponent = Cast<UUnitStateTreeAIComponent>(Owner->GetComponentByClass(UUnitStateTreeAIComponent::StaticClass()));
	if (StateTreeAIComponent)
	{
		//Send an event to the StateTree
		StateTreeAIComponent->SendStateTreeEvent(
			FStateTreeEvent(
				AIEventTags::EventResourceEmpty));
	}
}

void UResourceComponent::UpdateCollection(float DeltaTime)
{
	if (!bIsCollecting) return;

	// check if the resource node is valid
	if (!CurrentResourceNode.IsValid())
	{
		StopAndTriggerEmptyEvent();
		return;
	}

	// Why the extraction rate is determined by the resource node?
	float ExtractionAmount = CurrentResourceNode->GetExtRate() * DeltaTime;
	ExtractionAmount = CurrentResourceNode->ConsumeResource(
		ExtractionAmount
	);

	// Check if the resource node is empty
	if (CurrentResourceNode->GetQteDisponible() <= 0)
	{
		// TODO I should consider the multi-thread scenario, for I just destroy the node
		CurrentResourceNode->Destroy();
		StopAndTriggerEmptyEvent();
	}
	
	CarriedAmount += ExtractionAmount;
	// Check if the carried amount exceeds the max capacity
	if (CarriedAmount > CarriedMaxCapacity)
	{
		CarriedAmount = CarriedMaxCapacity;
		StopCollection();
	}
}

void UResourceComponent::StopCollection()
{
	if (!bIsCollecting) return;

	bIsCollecting = false;
	CurrentResourceNode = nullptr;
}

// -------------------- Deposit --------------------
void UResourceComponent::DepositResources()
{
	APlayerState* Player = GetPlayerState();
	if (!Player || CarriedAmount <= 0) return;

	if (AARTSGameState* GameState = Cast<AARTSGameState>(UGameplayStatics::GetGameState(GetWorld())))
	{
		GameState->AddResource(Player, CarriedResourceType, CarriedAmount);
	}

	CarriedAmount = 0;
}

// -------------------- Owner Resolution --------------------
APlayerState* UResourceComponent::GetPlayerState() const
{
	if (const AMiner* Miner = Cast<AMiner>(GetOwner()))
	{
		return Miner->GetOwningPlayerState();
	}

	if (const APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
		return OwnerPawn->GetPlayerState();
	}

	return nullptr;
}

// -------------------- Node Access --------------------
void UResourceComponent::SetCurrentResourceNode(AAResourceNode* NewNode)
{
	CurrentResourceNode = NewNode;
}

AAResourceNode* UResourceComponent::GetCurrentResourceNode() const
{
	return CurrentResourceNode.Get();
}

bool UResourceComponent::IsCollecting() const
{
	return bIsCollecting;
}

void UResourceComponent::SetDepositBaseTarget(ABaseBuilding* NewTarget)
{
	CurrentDepositBaseTarget = NewTarget;
}

ABaseBuilding* UResourceComponent::GetDepositBaseTarget() const
{
	return CurrentDepositBaseTarget.Get();
}
