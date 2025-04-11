#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AshesOfWar/Units/Interface/AOWInputInterface.h"
#include "Unit.generated.h"

// Forward declarations
class IAOWInputInterface;
class UAOWAbilitySystemComponent;
class UAOWAttributeSet;
class UGameplayAbility;
class UGameplayEffect;
class AUnitAIController;

/**
 * AUnit
 * Base class for all RTS units.
 * Integrates Gameplay Ability System (GAS), attributes, AI, and movement logic.
 */
UCLASS()
class ASHESOFWAR_API AUnit : public ACharacter, public IAbilitySystemInterface, public IAOWInputInterface
{
	GENERATED_BODY()

public:
	// Constructor
	AUnit();

	// Called once GAS and other components are initialized
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Initialization")
	void OnBeginPlay();
	virtual void OnBeginPlay_Implementation();

	// GAS requirement
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Returns this unit's attribute set
	virtual UAOWAttributeSet* GetAttributeSet() const;

	// Retrieves the unit's AI Controller
	TObjectPtr<AUnitAIController> GetAIController() const;

	// Issues a move command to the unit
	UFUNCTION(BlueprintCallable)
	void MoveToLocation(FVector TargetLocation);

	// Stops any current movement
	UFUNCTION(BlueprintCallable)
	void StopMovement();

	UFUNCTION(BlueprintCallable)
	void SetSelectedUnit(bool bSelected);

protected:
	// Called at spawn time
	virtual void BeginPlay() override;

	// Gives the unit its default gameplay abilities
	void GiveDefaultAbilities();

	// Applies the base gameplay effect that sets initial stats
	void InitDefaultAttributes();

	// --- GAS Components ---

	UPROPERTY(EditDefaultsOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAOWAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Attribute", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAOWAttributeSet> AttributeSet;

	// --- GAS Definitions (editable in Blueprint) ---

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UDecalComponent* DecalComponent;
};
