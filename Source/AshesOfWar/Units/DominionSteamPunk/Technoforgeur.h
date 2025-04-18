#pragma once

#include "CoreMinimal.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"
#include "Technoforgeur.generated.h"

/**
 * ATechnoforgeur
 * 
 * Special Steampunk worker unit: gathers resources, constructs buildings, and repairs nearby allies over time.
 */
UCLASS()
class ASHESOFWAR_API ATechnoforgeur : public AMiner
{
	GENERATED_BODY()

public:
	// Constructor
	ATechnoforgeur();

protected:
	/** Called when the unit is initialized. */
	virtual void BeginPlay() override;

	/** Starts the passive repair aura (called in BeginPlay). */
	void StartRepairAura();

	/** Periodically called function to heal nearby mechanical allies. */
	void RepairNearbyAllies();

protected:
	/** Timer handle for the repair aura effect. */
	FTimerHandle RepairAuraTimerHandle;

	/** Radius within which nearby units are repaired. */
	UPROPERTY(EditDefaultsOnly, Category = "Repair")
	float RepairRadius = 400.f;

	/** Amount of health restored per second to nearby units. */
	UPROPERTY(EditDefaultsOnly, Category = "Repair")
	float RepairAmountPerSecond = 5.f;
};
