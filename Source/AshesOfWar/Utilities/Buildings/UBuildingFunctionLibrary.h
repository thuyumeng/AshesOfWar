#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "UBuildingFunctionLibrary.generated.h"

/**
 * UBuildingFunctionLibrary
 * 
 * A static helper library containing building-related utility functions
 * for resource cost formatting and placement validation.
 */
UCLASS()
class ASHESOFWAR_API UBuildingFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Returns a formatted, readable version of a building's resource cost.
	 * Example: "100 Aetherium, 50 Vitae"
	 * 
	 * @param ResourceCost - Map containing resource types and their amounts.
	 * @return A FText representing the formatted resource costs.
	 */
	UFUNCTION(BlueprintPure, Category = "Building")
	static FText GetBuildingCostAsText(const TMap<EResourceType, int32>& ResourceCost);

	/**
	 * Checks if a building can be placed at a specific location using box collision testing.
	 * 
	 * @param World - The world context.
	 * @param Location - The center point to check.
	 * @param BoxExtent - Half size of the collision box.
	 * @return True if placement is valid (no obstacles), false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category = "Building")
	static bool CanPlaceBuildingHere(UWorld* World, const FVector& Location, const FVector& BoxExtent);
};
