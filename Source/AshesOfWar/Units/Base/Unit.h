// Core Unit class used for RTS characters with Ability System integration

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AshesOfWar/Units/Interface/AOWInputInterface.h"
#include "Unit.generated.h"


// Input interface for unit selection and control
class IAOWInputInterface;
// Forward declarations for performance (instead of full includes)
class UAOWAbilitySystemComponent;
class UAOWAttributeSet;
class UGameplayAbility;
class UGameplayEffect;

/**
 * AUnit
 * Base RTS Unit class that integrates GAS (Gameplay Ability System), attributes, and AI.
 */
UCLASS()
class ASHESOFWAR_API AUnit : public ACharacter, public IAbilitySystemInterface, public IAOWInputInterface
{
	GENERATED_BODY()

public:
	// Constructor – sets default values
	AUnit();

	// Called after BeginPlay for child classes to override logic
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Initialization")
	void OnBeginPlay();
	virtual void OnBeginPlay_Implementation();

	// GAS interface requirement
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Custom getter for this unit's attribute set
	virtual UAOWAttributeSet* GetAttributeSet() const;

	// Order unit to move to a given location (called via script/AI/blueprint)
	UFUNCTION(BlueprintCallable)
	void MoveToLocation(FVector TargetLocation);

	// Stop the unit's current movement
	UFUNCTION(BlueprintCallable)
	void StopMovement();

	// Interface function to get selected units (for input handling)
	virtual TArray<TObjectPtr<AUnit>> GetSelectedUnits() const override;

protected:
	// BeginPlay override to initialize GAS and custom attributes
	virtual void BeginPlay() override;

	// Grants the default gameplay abilities to the unit
	void GiveDefaultAbilities();

	// Initializes unit stats (health, speed, etc.) using a default effect
	void InitDefaultAttributes();

	// --- GAS Components ---

	UPROPERTY(EditDefaultsOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAOWAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Attribute", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAOWAttributeSet> AttributeSet;

	// --- GAS Definitions (Editor-configurable) ---

	// Abilities given to the unit on spawn
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	// Initial attribute modifier effect (e.g., sets default HP, Speed, Damage)
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;
};
