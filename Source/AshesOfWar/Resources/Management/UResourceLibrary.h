#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AshesOfWar/Resources/ResourcesTypes/FPlayerResourceData.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "UResourceLibrary.generated.h"

/**
 * Static utility library for handling resource-related operations.
 * Includes helper functions to retrieve player resource data and check affordability.
 */
UCLASS()
class ASHESOFWAR_API UResourceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Retrieves a copy of the resource data for the specified player.
	 * @param Player - The PlayerState to fetch resources from.
	 * @return A copy of the player's current resource data (Aetherium, Vitae, Umbra).
	 */
	UFUNCTION(BlueprintCallable, Category = "Resource")
	static FPlayerResourceData GetResourcesForPlayer(APlayerState* Player);

	/**
	 * Checks if the specified player has enough resources to afford a given cost.
	 * @param Player - The PlayerState to check.
	 * @param Cost - The cost to evaluate against the player's current resources.
	 * @return True if the player has enough of each resource, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Resource")
	static bool CanAfford(APlayerState* Player, const FPlayerResourceData& Cost);
};
