// --- Header Guard & Metadata ---
#pragma once

// --- Includes ---
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AOWAbilitySystemComponent.generated.h"

/**
 * UAOWAbilitySystemComponent
 * 
 * Custom Ability System Component for Ashes of War RTS.
 * Manages abilities and gameplay effects for units and heroes.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASHESOFWAR_API UAOWAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// --- Constructor ---
	UAOWAbilitySystemComponent();

protected:
	// --- Lifecycle ---
	virtual void BeginPlay() override;

	// TODO: You can override InitAbilityActorInfo() or add helper methods to grant default abilities later.
};
