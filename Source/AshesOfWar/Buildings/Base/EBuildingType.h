#pragma once
#include "CoreMinimal.h"
#include "EBuildingType.generated.h"

UENUM(BlueprintType)
enum class EBuildingType : uint8
{
	HQ UMETA(DisplayName = "HQ"),
	Production UMETA(DisplayName = "Production"),
	Defense UMETA(DisplayName = "Defense"),
	Research UMETA(DisplayName = "Research")

};
