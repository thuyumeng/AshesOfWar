// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Unit.generated.h"

// forward declarations of the gameplay ability system classes
class UAOWAbilitySystemComponent;
class UAOWAttributeSet;
class UGameplayAbility;
class UGameplayEffect;

UCLASS()
class ASHESOFWAR_API AUnit : public ACharacter, public IAbilitySystemInterface{
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  AUnit();
  // Implement IAbilitySystemInterface
  virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
  // End of implementation of IAbilitySystemInterface

  virtual UAOWAttributeSet* GetAttributeSet() const;
protected:
  // Begin play to initialize the Ability and Attribute
  virtual void BeginPlay() override;
  // Give the ability to a unit should be done in the server
  void GiveDefaultAbilities();
  // Initialize the default abilities of the unit, Can be s
  void InitDefaultAttributes();

  // the reference to the ability system objects
  UPROPERTY()
  TObjectPtr<UAOWAbilitySystemComponent> AbilitySystemComponent;
  UPROPERTY()
  TObjectPtr<UAOWAttributeSet> AttributeSet;

  // Can be set in the editor to assign default abilities to the unit
  UPROPERTY(EditDefaultsOnly, Category = "Ability")
  TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

  // The default attribute effect to apply to the unit(initialize the attributes)
  UPROPERTY(EditDefaultsOnly, Category = "Ability")
  TSubclassOf<UGameplayEffect> DefaultAttributeEffect;
};
