#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBuildingInterface.generated.h"

/**
 * UBuildingInterface
 * 
 * Unreal-specific boilerplate for creating a building-related interface.
 * Use this interface to define core events like construction, damage, and repair.
 */
UINTERFACE(MinimalAPI)
class UBuildingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * IBuildingInterface
 * 
 * Interface that building actors must implement to react to construction, damage, and repair events.
 */
class ASHESOFWAR_API IBuildingInterface
{
	GENERATED_BODY()

public:
	/**
	 * Called when the building is fully constructed.
	 */
	virtual void OnConstructed() = 0;

	/**
	 * Called when the building takes damage.
	 * @param DamageAmount - Amount of damage received.
	 */
	virtual void OnDamaged(float DamageAmount) = 0;

	/**
	 * Called when the building is repaired.
	 * @param RepairAmount - Amount of health restored.
	 */
	virtual void OnRepaired(float RepairAmount) = 0;
};
