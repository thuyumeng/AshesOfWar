#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBuildingInterface.generated.h"

UINTERFACE(MinimalAPI)
class UBuildingInterface : public UInterface
{
	GENERATED_BODY()
};

class ASHESOFWAR_API IBuildingInterface
{
	GENERATED_BODY()

public:
	//* Ajouter : Méthodes comme OnConstructed(), OnDamaged(), OnRepaired() *//
};