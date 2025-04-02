#include "UResourceComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "AshesOfWar/Core/GameStates/ARTSGameState.h"
#include "GameFramework/PlayerState.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"

UResourceComponent::UResourceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Default values
	bIsCollecting = false;
	CarriedAmount = 0;
	CarriedResourceType = EResourceType::Aetherium; // Default to Aetherium
	CarriedMaxCapacity = 50;
	CurrentResourceNode = nullptr;
}

void UResourceComponent::BeginCollection()
{
	// TODO: Re-check logic so it works properly with units

	if (!CurrentResourceNode || bIsCollecting)
		return;

	// Begin the collection process
	bIsCollecting = true;
	CarriedResourceType = CurrentResourceNode->GetResourceType();

	// Determine how much to collect based on available quantity and extraction rate
	int32 AvailableToExtract = FMath::Min(CurrentResourceNode->GetQteDisponible(), CarriedMaxCapacity);
	int32 Extracted = FMath::Min(AvailableToExtract, CurrentResourceNode->GetExtRate());

	CarriedAmount = Extracted;

	// Update the remaining amount on the resource node
	int32 NewQte = CurrentResourceNode->GetQteDisponible() - Extracted;
	CurrentResourceNode->SetQteDisponible(NewQte);
}

void UResourceComponent::StopCollection()
{
	// TODO: Re-check logic so it works properly with units

	// Stop the collection process and reset node reference
	bIsCollecting = false;
	CurrentResourceNode = nullptr;
}

APlayerState* UResourceComponent::GetPlayerState() const
{
	// Attempt to cast the owner to a pawn and return its PlayerState
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return nullptr;

	return OwnerPawn->GetPlayerState();
}

void UResourceComponent::DepositResources()
{
	// TODO: Re-check logic so it works properly with units

	// TODO: Implement logic to deposit carried resources into a structure (e.g., HQ or depot)
}
