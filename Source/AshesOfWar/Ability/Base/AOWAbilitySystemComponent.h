// This file is the ability system component for the game. It is used to manage the abilities of the game characters.

#pragma once

// Base Ability System Component from Unreal's GameplayAbilitySystem module
#include "AbilitySystemComponent.h"

// Core Unreal headers (required for most classes and types)
#include "CoreMinimal.h"

// Automatically generated header for this component class
#include "AOWAbilitySystemComponent.generated.h"

/**
 * UAOWAbilitySystemComponent
 * Custom Ability System Component for managing abilities and gameplay effects in Ashes of War.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASHESOFWAR_API UAOWAbilitySystemComponent : public UAbilitySystemComponent {
  GENERATED_BODY()

public:
  // Constructor: Sets default values for this component's properties
  UAOWAbilitySystemComponent();

protected:
  // Called when the game starts (e.g., on actor spawn)
  virtual void BeginPlay() override;

  // You can later override functions like InitAbilityActorInfo or implement granting default abilities
};

