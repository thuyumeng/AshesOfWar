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
	virtual void OnConstructed() = 0;
	virtual void OnDamaged(float DamageAmount) = 0;
	virtual void OnRepaired(float RepairAmount) = 0;
};
