// Custom StateTree AI component for RTS units in Ashes of War

#pragma once

#include "CoreMinimal.h"
#include "Components/StateTreeAIComponent.h"
#include "UnitStateTreeAIComponent.generated.h"

/**
 * UUnitStateTreeAIComponent
 * Specialized AI component using the StateTree system to drive unit behavior logic.
 */
UCLASS(ClassGroup = (AI), meta = (BlueprintSpawnableComponent))
class ASHESOFWAR_API UUnitStateTreeAIComponent : public UStateTreeAIComponent
{
	GENERATED_BODY()

public:
	// Constructor – sets default values for this component
	UUnitStateTreeAIComponent();

protected:
	// Called when the game starts or the owning actor is spawned
	virtual void BeginPlay() override;

public:
	/**
	 * Assigns a new StateTree asset at runtime.
	 * Useful for dynamically switching AI logic trees based on conditions.
	 */
	UFUNCTION(BlueprintCallable, Category = "StateTree")
	void SetStateTree(UStateTree* NewStateTree);
};
