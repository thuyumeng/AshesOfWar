#pragma once

// --- Includes ---
#include "CoreMinimal.h"
#include "Components/StateTreeAIComponent.h"
#include "UnitStateTreeAIComponent.generated.h"

/**
 * UUnitStateTreeAIComponent
 * 
 * Custom AI component for RTS units that uses the StateTree system
 * to manage behavior logic dynamically.
 */
UCLASS(ClassGroup = (AI), meta = (BlueprintSpawnableComponent))
class ASHESOFWAR_API UUnitStateTreeAIComponent : public UStateTreeAIComponent
{
	GENERATED_BODY()

public:
	// --- Constructor ---
	UUnitStateTreeAIComponent();

protected:
	// --- Lifecycle ---
	virtual void BeginPlay() override;

public:
	/**
	 * Assigns a new StateTree asset dynamically and reinitializes logic.
	 */
	UFUNCTION(BlueprintCallable, Category = "StateTree")
	void SetStateTree(UStateTree* NewStateTree);
};
