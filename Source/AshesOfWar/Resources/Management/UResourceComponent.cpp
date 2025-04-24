#include "UResourceComponent.h"
#include "AshesOfWar/Core/GameStates/ARTSGameState.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Pawn.h"

// --- Constructor ---
UResourceComponent::UResourceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	bIsCollecting = false;
	CarriedAmount = 0;
	CarriedMaxCapacity = 50;
	CarriedResourceType = EResourceType::Aetherium;
	CurrentResourceNode = nullptr;
}

// --- Start resource collection ---
void UResourceComponent::BeginCollection()
{
	if (!CurrentResourceNode || bIsCollecting)
	{
		return;
	}

	CarriedResourceType = CurrentResourceNode->GetResourceType();

	const int32 Available = CurrentResourceNode->GetQteDisponible();
	const int32 ExtractionRate = CurrentResourceNode->GetExtRate();

	if (Available <= 0 || ExtractionRate <= 0)
	{
		return;
	}

	const int32 MaxExtractable = FMath::Min(CarriedMaxCapacity, Available);
	const int32 AmountExtracted = FMath::Min(MaxExtractable, ExtractionRate);

	CarriedAmount = AmountExtracted;
	CurrentResourceNode->SetQteDisponible(Available - AmountExtracted);
	bIsCollecting = true;
}

// --- Stop resource collection ---
void UResourceComponent::StopCollection()
{
	if (!bIsCollecting) return;

	bIsCollecting = false;
	CurrentResourceNode = nullptr;
}

// --- Deposit carried resources ---
void UResourceComponent::DepositResources()
{
	APlayerState* Player = GetPlayerState();
	if (!Player || CarriedAmount <= 0) return;

	AARTSGameState* GameState = Cast<AARTSGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (!GameState) return;

	GameState->AddResource(Player, CarriedResourceType, CarriedAmount);

	CarriedAmount = 0;
	bIsCollecting = false;
}

// --- Determine owning player ---
APlayerState* UResourceComponent::GetPlayerState() const
{
	if (const AMiner* Miner = Cast<AMiner>(GetOwner()))
	{
		if (APlayerState* State = Miner->GetOwningPlayerState())
		{
			return State;
		}
	}

	if (const APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
		return OwnerPawn->GetPlayerState();
	}

	return nullptr;
}

// --- Node Accessors ---
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
