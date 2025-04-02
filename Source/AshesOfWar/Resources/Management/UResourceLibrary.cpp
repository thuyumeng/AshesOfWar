#include "UResourceLibrary.h"
#include "AshesOfWar/Core/GameStates/ARTSGameState.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"

FPlayerResourceData UResourceLibrary::GetResourcesForPlayer(APlayerState* Player)
{
	FPlayerResourceData OutResources;

	// Validate input
	if (!Player)
	{
		return OutResources;
	}

	// Get the current game state and cast it to our custom game state
	AARTSGameState* GameState = Cast<AARTSGameState>(UGameplayStatics::GetGameState(Player->GetWorld()));
	if (!GameState)
	{
		return OutResources;
	}

	// Retrieve the player's current resources from the game state's map
	if (const FPlayerResourceData* ResourcePtr = GameState->PlayerResources.Find(Player))
	{
		OutResources = *ResourcePtr;
	}

	return OutResources;
}

bool UResourceLibrary::CanAfford(APlayerState* Player, const FPlayerResourceData& Cost)
{
	// Validate input
	if (!Player)
	{
		return false;
	}

	// Get the current game state and cast it to our custom game state
	AARTSGameState* GameState = Cast<AARTSGameState>(UGameplayStatics::GetGameState(Player->GetWorld()));
	if (!GameState)
	{
		return false;
	}

	// Check if the player exists in the resource map
	const FPlayerResourceData* PlayerRes = GameState->PlayerResources.Find(Player);
	if (!PlayerRes)
	{
		return false;
	}

	// Compare player resources to the requested cost
	return PlayerRes->Aetherium >= Cost.Aetherium &&
		   PlayerRes->Vitae    >= Cost.Vitae &&
		   PlayerRes->Umbra    >= Cost.Umbra;
}
