#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UBuildingAuraComponent.generated.h"

// Forward declaration
class UGameplayEffect;

/**
 * UBuildingAuraComponent
 * 
 * Actor component responsible for applying an aura (buff or debuff) to nearby units.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASHESOFWAR_API UBuildingAuraComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Constructor
	UBuildingAuraComponent();

protected:
	/** 
	 * Called when the game starts.
	 */
	virtual void BeginPlay() override;

	/** 
	 * Called every frame to apply the aura effect dynamically.
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Scans for nearby units and applies or refreshes the aura effect.
	 */
	void ApplyAuraToNearbyUnits();

private:
	/** Radius of the aura effect in Unreal units (centimeters). */
	UPROPERTY(EditAnywhere, Category = "Aura")
	float AuraRadius;

	/** 
	 * Defines whether the aura is a positive buff or a negative debuff.
	 * True = Buff, False = Debuff.
	 */
	UPROPERTY(EditAnywhere, Category = "Aura")
	bool bIsBuff;

	/** Gameplay effect class representing the aura effect to apply. */
	UPROPERTY(EditAnywhere, Category = "Aura")
	TSubclassOf<UGameplayEffect> AuraEffect;

	/** List of currently affected units to manage application efficiently. */
	UPROPERTY()
	TArray<AActor*> AffectedUnits;
};
