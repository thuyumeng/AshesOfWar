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
	// Validation : node invalide ou déjà en train de collecter
	if (!CurrentResourceNode || bIsCollecting)
	{
		UE_LOG(LogTemp, Warning, TEXT("UResourceComponent::BeginCollection - CurrentResourceNode is invalid or already collecting."));
		return;
	}

	// Récupérer le type de ressource
	CarriedResourceType = CurrentResourceNode->GetResourceType();

	// Déterminer la quantité possible à extraire
	const int32 Disponible = CurrentResourceNode->GetQteDisponible();
	const int32 Taux = CurrentResourceNode->GetExtRate();

	if (Disponible <= 0 || Taux <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UResourceComponent::BeginCollection - Node épuisé ou extraction rate nul."));
		return;
	}

	const int32 ExtractionMax = FMath::Min(CarriedMaxCapacity, Disponible);
	const int32 QuantitéExtraite = FMath::Min(ExtractionMax, Taux);

	// Appliquer la quantité extraite
	CarriedAmount = QuantitéExtraite;
	CurrentResourceNode->SetQteDisponible(Disponible - QuantitéExtraite);

	// Marquer comme en collecte
	bIsCollecting = true;

	UE_LOG(LogTemp, Log, TEXT("UResourceComponent::BeginCollection - Collecté %d de %s"), QuantitéExtraite, *UEnum::GetValueAsString(CarriedResourceType));
}


void UResourceComponent::StopCollection()
{
	if (!bIsCollecting)
	{
		UE_LOG(LogTemp, Warning, TEXT("UResourceComponent::StopCollection - Pas en cours de collecte."));
		return;
	}

	bIsCollecting = false;
	CurrentResourceNode = nullptr;

	UE_LOG(LogTemp, Log, TEXT("UResourceComponent::StopCollection - Collecte arrêtée."));
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
	APlayerState* Player = GetPlayerState();
	if (!Player || CarriedAmount <= 0) return;

	AARTSGameState* GameState = Cast<AARTSGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (!GameState) return;

	// Ajouter la ressource au GameState
	GameState->AddResource(Player, CarriedResourceType, CarriedAmount);

	// Reset du contenu transporté
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
