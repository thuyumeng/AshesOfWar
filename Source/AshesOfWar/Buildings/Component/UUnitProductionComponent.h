#pragma once

// --- Includes ---
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UUnitProductionComponent.generated.h"

// --- Forward Declarations ---
class AUnit;

/**
 * UUnitProductionComponent
 * 
 * Handles time-based unit production for RTS buildings.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASHESOFWAR_API UUnitProductionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// --- Constructor ---
	UUnitProductionComponent();

	// --- Public API ---

	/** Starts production of a unit of the given class. */
	UFUNCTION(BlueprintCallable, Category = "Production")
	void StartProduction(TSubclassOf<AUnit> UnitClass);

	/** Cancels any active unit production. */
	UFUNCTION(BlueprintCallable, Category = "Production")
	void CancelProduction();

	/** Returns true if the building is currently producing a unit. */
	UFUNCTION(BlueprintPure, Category = "Production")
	bool IsProducing() const;

protected:
	// --- Lifecycle Hooks ---
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// --- Production State ---
	UPROPERTY()
	TSubclassOf<AUnit> CurrentUnitClass;

	UPROPERTY()
	float TimeRemaining;

	UPROPERTY()
	float TotalProductionTime;

	UPROPERTY()
	bool bIsProducing;
};
