#pragma once
#include "CoreMinimal.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "AshesOfWar/Buildings/Base/EBuildingType.h"
#include "FBuildingInfo.generated.h"

USTRUCT(BlueprintType)
struct FBuildingInfo
{
	GENERATED_BODY();

	//* Nom interne / ID *//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName BuildingID;

	//* Type de bâtiment (Production, QG, etc.) *//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EBuildingType BuildingType;

	//* Coût par ressource (Aetherium, Vitae, Umbra) *//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EResourceType, int32> ResourceCost;

	//* Temps de construction *//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ConstructionTime;

	//* Tier minimum requis *//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 RequiredTechTier;

	//* PV Max du bâtiment *//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxHealth;
};
