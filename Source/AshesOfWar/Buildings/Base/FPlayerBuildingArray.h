#pragma once

#include "CoreMinimal.h"
#include "FPlayerBuildingArray.generated.h"

// Forward declaration to minimize dependencies
class ABaseBuilding;

/**
 * FPlayerBuildingArray
 *
 * Structure used to store a list of all buildings owned by a player.
 */
USTRUCT()
struct FPlayerBuildingArray
{
	GENERATED_BODY()

	/** Array of building instances owned by the player. */
	UPROPERTY()
	TArray<TObjectPtr<ABaseBuilding>> Buildings;
};
