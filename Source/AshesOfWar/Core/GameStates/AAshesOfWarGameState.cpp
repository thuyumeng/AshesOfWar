#include "AAshesOfWarGameState.h"
#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"
#include "AshesOfWar/Buildings/Base/FPlayerBuildingArray.h"
#include "GameFramework/PlayerState.h"

// Ajoute un bâtiment à la liste du joueur
void AAshesOfWarGameState::RegisterBuilding(APlayerState* Player, ABaseBuilding* Building)
{
	if (!Player || !Building) return;

	if (!PlayerBuildings.Contains(Player))
	{
		PlayerBuildings.Add(Player, FPlayerBuildingArray());
	}

	PlayerBuildings[Player].Buildings.Add(Building);
}

// Récupère tous les bâtiments d’un type donné (ex : Production)
TArray<ABaseBuilding*> AAshesOfWarGameState::GetBuildingsOfType(APlayerState* Player, EBuildingType Type) const
{
	TArray<ABaseBuilding*> Matching;

	if (!Player || !PlayerBuildings.Contains(Player)) return Matching;

	for (ABaseBuilding* Building : PlayerBuildings[Player].Buildings)
	{
		if (Building && Building->BuildingData.BuildingType == Type)
		{
			Matching.Add(Building);
		}
	}

	return Matching;
}

// Récupère le niveau de tier du joueur (default = 1 si non initialisé)
int32 AAshesOfWarGameState::GetTechTierForPlayer(APlayerState* Player) const
{
	if (!Player) return 1;

	if (const int32* Tier = PlayerTechTier.Find(Player))
	{
		return *Tier;
	}

	return 1;
}
