// This file is the ability system component for the game. It is used to manage the abilities of the game characters.

#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "AOWAbilitySystemComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASHESOFWAR_API UAOWAbilitySystemComponent : public UAbilitySystemComponent {
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UAOWAbilitySystemComponent();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;
};
