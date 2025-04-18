#pragma once

#include "CoreMinimal.h"
#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"
#include "FlyingBase.generated.h"

// Forward declarations
class UUnitProductionComponent;
class AUnit;

/**
 * AFlyingBase
 * 
 * Primary HQ building for the Steampunk faction.
 * Allows basic unit production (currently Miner units).
 * Also features a levitation effect for visual flair.
 */
UCLASS()
class ASHESOFWAR_API AFlyingBase : public ABaseBuilding
{
	GENERATED_BODY()

public:
	// Constructor
	AFlyingBase();

protected:
	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

	/** Called every frame to apply levitation visual effect. */
	virtual void Tick(float DeltaTime) override;

public:
	/**
	 * Initiates production of a specific unit class.
	 */
	UFUNCTION(BlueprintCallable, Category = "Production")
	void ProduceUnit(TSubclassOf<AUnit> UnitClass);

private:
	/** Component responsible for handling unit production logic. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Production", meta = (AllowPrivateAccess = "true"))
	UUnitProductionComponent* UnitProductionComponent;

	// --- Levitation effect variables ---

	/** Maximum vertical amplitude of the levitation (units in centimeters). */
	UPROPERTY(EditDefaultsOnly, Category = "Flying Effect")
	float LevitationAmplitude = 20.f;

	/** Speed of the levitation oscillation (higher is faster). */
	UPROPERTY(EditDefaultsOnly, Category = "Flying Effect")
	float LevitationSpeed = 2.f;

	/** Saved initial Z-axis position for stable oscillation calculations. */
	float InitialZ = 0.f;
};
