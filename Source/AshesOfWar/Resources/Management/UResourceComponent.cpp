#include "UResourceComponent.h"
#include "AshesOfWar/Core/GameStates/ARTSGameState.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"
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
	if (!CurrentResourceNode) return;

	CarriedResourceType = CurrentResourceNode->GetResourceType();

	const int32 Available = CurrentResourceNode->GetQteDisponible();
	const int32 ExtractionRate = CurrentResourceNode->GetExtRate();

	if (Available <= 0 || ExtractionRate <= 0) return;

	bIsCollecting = true;
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
	bIsCollecting = false;
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
	return CurrentResourceNode;
}

bool UResourceComponent::IsCollecting() const
{
	return bIsCollecting;
}
