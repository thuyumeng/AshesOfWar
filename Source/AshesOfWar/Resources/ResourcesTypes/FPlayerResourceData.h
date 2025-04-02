#pragma once

#include "CoreMinimal.h"
#include "FPlayerResourceData.generated.h"

/**
 * Struct representing the resource data of a player.
 * Contains the amount of each resource type: Aetherium, Vitae, and Umbra.
 */
USTRUCT(BlueprintType)
struct ASHESOFWAR_API FPlayerResourceData
{
	GENERATED_BODY()

	// Amount of Aetherium (main resource used for most actions)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int32 Aetherium = 0;

	// Amount of Vitae (used for mid-tier units and abilities)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int32 Vitae = 0;

	// Amount of Umbra (used for high-tier buildings and tech)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int32 Umbra = 0;
};
