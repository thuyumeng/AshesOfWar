// AI Controller class for RTS units in Ashes of War

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "UnitAIController.generated.h"

// Forward declaration to avoid unnecessary includes in the header
class UUnitStateTreeAIComponent;

/**
 * AUnitAIController
 * Custom AIController class managing RTS unit behavior via StateTree.
 */
UCLASS()
class ASHESOFWAR_API AUnitAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Constructor: Initializes this AI Controller with a StateTree component
	explicit AUnitAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// AI logic component using Unreal's StateTree system
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UUnitStateTreeAIComponent> UnitStateTreeAIComponent;

	// Function to get the StateTree component
	UFUNCTION(BlueprintCallable, Category = "AI")
	UUnitStateTreeAIComponent* GetUnitStateTreeAIComponent() const
	{
		return UnitStateTreeAIComponent;
	}
protected:
	// Called when the game begins or this controller is spawned
	virtual void BeginPlay() override;

	// You may later override Tick() or Possess() here for advanced logic
};
