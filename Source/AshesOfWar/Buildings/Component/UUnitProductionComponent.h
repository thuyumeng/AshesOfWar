#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UUnitProductionComponent.generated.h"

// Forward declaration
class AUnit;

/**
 * UUnitProductionComponent
 *
 * Handles the production (spawning) of units by buildings over time.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASHESOFWAR_API UUnitProductionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Constructor
	UUnitProductionComponent();

	/**
	 * Starts the production of a specified unit class.
	 */
	UFUNCTION(BlueprintCallable, Category = "Production")
	void StartProduction(TSubclassOf<AUnit> UnitClass);

	/**
	 * Cancels any ongoing production process.
	 */
	UFUNCTION(BlueprintCallable, Category = "Production")
	void CancelProduction();

	/**
	 * Returns whether the component is currently producing a unit.
	 */
	UFUNCTION(BlueprintPure, Category = "Production")
	bool IsProducing() const;

protected:
	/** Called when the game starts. */
	virtual void BeginPlay() override;

	/** Called every frame to update production progress. */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/** The unit class currently being produced. */
	UPROPERTY()
	TSubclassOf<AUnit> CurrentUnitClass;

	/** Remaining time before production completes. */
	UPROPERTY()
	float TimeRemaining;

	/** Total time required to produce the current unit. */
	UPROPERTY()
	float TotalProductionTime;

	/** Whether a unit is currently in production. */
	UPROPERTY()
	bool bIsProducing;
};
