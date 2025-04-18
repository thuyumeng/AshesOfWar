#pragma once

#include "CoreMinimal.h"
#include "EBuildingType.generated.h"

/**
 * Enumeration representing different building categories in the RTS game.
 */
UENUM(BlueprintType)
enum class EBuildingType : uint8
{
	/** Headquarters - main building that enables base development. */
	HQ UMETA(DisplayName = "HQ"),

	/** Production building - used to create units or gather resources. */
	Production UMETA(DisplayName = "Production"),

	/** Defensive structure - designed to protect the base. */
	Defense UMETA(DisplayName = "Defense"),

	/** Research facility - unlocks upgrades and technologies. */
	Research UMETA(DisplayName = "Research")
};
