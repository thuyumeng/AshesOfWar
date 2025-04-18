#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AshesOfWar/Buildings/Base/EBuildingType.h"
#include "AshesOfWar/Buildings/Base/FPlayerBuildingArray.h"
#include "AAshesOfWarGameState.generated.h"

// Forward declaration
class ABaseBuilding;

/**
 * AAshesOfWarGameState
 *
 * Custom GameState for Ashes of War, responsible for tracking player buildings and technological tiers.
 */
UCLASS()
class ASHESOFWAR_API AAshesOfWarGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	/**
	 * Registers a new building to the owning player's building list.
	 */
	UFUNCTION(BlueprintCallable, Category = "Building")
	void RegisterBuilding(APlayerState* Player, ABaseBuilding* Building);

	/**
	 * Retrieves all buildings of a specified type belonging to a player.
	 */
	UFUNCTION(BlueprintCallable, Category = "Building")
	TArray<ABaseBuilding*> GetBuildingsOfType(APlayerState* Player, EBuildingType Type) const;

	/**
	 * Retrieves the current technological tier of the player (default = 1 if uninitialized).
	 */
	UFUNCTION(BlueprintCallable, Category = "Building")
	int32 GetTechTierForPlayer(APlayerState* Player) const;

protected:
	/** List of buildings owned by each player. */
	UPROPERTY()
	TMap<TObjectPtr<APlayerState>, FPlayerBuildingArray> PlayerBuildings;

private:
	/** Tech tier per player. */
	UPROPERTY()
	TMap<TObjectPtr<APlayerState>, int32> PlayerTechTier;
};
