#pragma once
#include "CoreMinimal.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "FBuildingInfo.generated.h"

USTRUCT(BlueprintType)
struct FBuildingInfo
{
	GENERATED_BODY()

public:
	//* Ajouter : Champs pour coût (TMap<EResourceType, int32>), HP, temps construction, type *//
	//* Utilisé pour définir chaque bâtiment sans dupliquer dans chaque classe *//
};