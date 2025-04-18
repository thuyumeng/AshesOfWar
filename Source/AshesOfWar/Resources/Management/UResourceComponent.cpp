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
	CarriedResourceType = EResourceType::Aetherium; // Default resource type
	CarriedMaxCapacity = 50;
	CurrentResourceNode = nullptr;
}

void UResourceComponent::BeginCollection()
{
	// Validation: invalid node or already collecting
	if (!CurrentResourceNode || bIsCollecting)
	{
		UE_LOG(LogTemp, Warning, TEXT("UResourceComponent::BeginCollection - CurrentResourceNode is invalid or already collecting."));
		return;
	}

	// Get the resource type
	CarriedResourceType = CurrentResourceNode->GetResourceType();

	// Determine available extraction amount
	const int32 Available = CurrentResourceNode->GetQteDisponible();
	const int32 ExtractionRate = CurrentResourceNode->GetExtRate();

	if (Available <= 0 || ExtractionRate <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UResourceComponent::BeginCollection - Node depleted or extraction rate is zero."));
		return;
	}

	const int32 MaxExtractable = FMath::Min(CarriedMaxCapacity, Available);
	const int32 AmountExtracted = FMath::Min(MaxExtractable, ExtractionRate);

	// Apply extracted quantity
	CarriedAmount = AmountExtracted;
	CurrentResourceNode->SetQteDisponible(Available - AmountExtracted);

	// Mark as collecting
	bIsCollecting = true;

	UE_LOG(LogTemp, Log, TEXT("UResourceComponent::BeginCollection - Collected %d of %s"), AmountExtracted, *UEnum::GetValueAsString(CarriedResourceType));
}

void UResourceComponent::StopCollection()
{
	if (!bIsCollecting)
	{
		UE_LOG(LogTemp, Warning, TEXT("UResourceComponent::StopCollection - Not currently collecting."));
		return;
	}

	bIsCollecting = false;
	CurrentResourceNode = nullptr;

	UE_LOG(LogTemp, Log, TEXT("UResourceComponent::StopCollection - Collection stopped."));
}

APlayerState* UResourceComponent::GetPlayerState() const
{
	// Try to cast the owner to a Pawn and get its PlayerState
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		return nullptr;
	}

	return OwnerPawn->GetPlayerState();
}

void UResourceComponent::DepositResources()
{
	APlayerState* Player = GetPlayerState();
	if (!Player || CarriedAmount <= 0)
	{
		return;
	}

	AARTSGameState* GameState = Cast<AARTSGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (!GameState)
	{
		return;
	}

	// Add the carried resource to the player's resource pool
	GameState->AddResource(Player, CarriedResourceType, CarriedAmount);

	// Reset carried contents
	CarriedAmount = 0;
	bIsCollecting = false;
}

void UResourceComponent::SetCurrentResourceNode(AAResourceNode* NewNode)
{
	CurrentResourceNode = NewNode;
}

AAResourceNode* UResourceComponent::GetCurrentResourceNode() const
{
	return CurrentResourceNode;
}

bool UResourceComponent::IsCollecting() const
{
	return bIsCollecting;
}
