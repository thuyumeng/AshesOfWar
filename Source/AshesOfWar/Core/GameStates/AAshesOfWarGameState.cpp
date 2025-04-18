#include "AAshesOfWarGameState.h"
#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"
#include "GameFramework/PlayerState.h"

void AAshesOfWarGameState::RegisterBuilding(APlayerState* Player, ABaseBuilding* Building)
{
	if (!Player || !Building)
	{
		return;
	}

	// Ensure the player entry exists
	if (!PlayerBuildings.Contains(Player))
	{
		PlayerBuildings.Add(Player, FPlayerBuildingArray());
	}

	// Add the building to the player's list
	PlayerBuildings[Player].Buildings.Add(Building);
}

TArray<ABaseBuilding*> AAshesOfWarGameState::GetBuildingsOfType(APlayerState* Player, EBuildingType Type) const
{
	TArray<ABaseBuilding*> MatchingBuildings;

	if (!Player || !PlayerBuildings.Contains(Player))
	{
		return MatchingBuildings;
	}

	for (ABaseBuilding* Building : PlayerBuildings[Player].Buildings)
	{
		if (Building && Building->BuildingData.BuildingType == Type)
		{
			MatchingBuildings.Add(Building);
		}
	}

	return MatchingBuildings;
}

int32 AAshesOfWarGameState::GetTechTierForPlayer(APlayerState* Player) const
{
	if (!Player)
	{
		return 1;
	}

	if (const int32* Tier = PlayerTechTier.Find(Player))
	{
		return *Tier;
	}

	// Default starting tech tier if not registered yet
	return 1;
}
