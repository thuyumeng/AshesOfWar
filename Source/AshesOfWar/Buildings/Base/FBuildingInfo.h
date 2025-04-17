#pragma once

#include "CoreMinimal.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "AshesOfWar/Buildings/Base/EBuildingType.h"
#include "FBuildingInfo.generated.h"

/**
 * FBuildingInfo
 *
 * Structure defining essential data for buildings (cost, type, construction time, etc.).
 */
USTRUCT(BlueprintType)
struct FBuildingInfo
{
	GENERATED_BODY()

	/** Internal name / ID used to reference the building. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName BuildingID;

	/** Type of the building (e.g., Production, HQ, Defense, Research). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EBuildingType BuildingType;

	/** Resource cost to construct the building (Aetherium, Vitae, Umbra). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EResourceType, int32> ResourceCost;

	/** Construction time in seconds. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ConstructionTime;

	/** Minimum tech tier required to unlock this building. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 RequiredTechTier;

	/** Maximum health points of the building. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxHealth;
};
