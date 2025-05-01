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
class UStateTree;

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
	virtual void PostInitializeComponents() override;

	// Gives the unit its default gameplay abilities
	void GiveDefaultAbilities();

	// Initialze the default attributes for the unit
	void InitDefaultAttributes();

	// Utility function to set the attributeSet by the CurveTable
	void InitAttributeSetsByCurveTables(const FName& GroupName, int32 Level=1, bool bInitialInit=true);

	// Overridden by subclasses to initialize their specific attributes
	virtual void InitAttributeSets();

	// Initialize the decal
	void InitializeDecal();

	// --- GAS Components ---

	UPROPERTY(EditDefaultsOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAOWAbilitySystemComponent> AbilitySystemComponent;
	
	// --- GAS Definitions (editable in Blueprint) ---

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<UCurveTable*> AttributeSetsTables;
	
	// --- The DecalComponent for selection
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UDecalComponent* DecalComponent;

	// --- The AI Component for the unit
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UStateTree* StateTreeAsset;
};
