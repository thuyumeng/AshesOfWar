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
		UE_LOG(LogTemp, Warning, TEXT("⛔ Impossible de commencer la collecte : node invalide ou déjà en cours."));
		return;
	}

	CarriedResourceType = CurrentResourceNode->GetResourceType();

	const int32 Available = CurrentResourceNode->GetQteDisponible();
	const int32 ExtractionRate = CurrentResourceNode->GetExtRate();

	if (Available <= 0 || ExtractionRate <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("❌ Node vide ou taux d'extraction invalide. Minage annulé."));
		return;
	}

	// Activation seulement, pas d'extraction ici
	bIsCollecting = true;

	// Log unique à l’init
	UE_LOG(LogTemp, Warning, TEXT("[⛏️ Collection Init] Début du minage | Node: %d | Taux: %d/sec | Type: %s"),
		Available,
		ExtractionRate,
		*UEnum::GetValueAsString(CarriedResourceType));
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
