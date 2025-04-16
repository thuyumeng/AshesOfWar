#pragma once

#include "CoreMinimal.h"
#include "FPlayerBuildingArray.generated.h"

class ABaseBuilding;

USTRUCT()
struct FPlayerBuildingArray
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<ABaseBuilding>> Buildings;
};
