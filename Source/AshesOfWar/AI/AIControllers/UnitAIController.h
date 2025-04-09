#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitAIController.generated.h"

class UUnitStateTreeAIComponent;

/**
 * AUnitAIController
 * Custom AI controller that manages RTS unit behavior using a StateTree component.
 */
UCLASS()
class ASHESOFWAR_API AUnitAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Constructor: Initializes the AI controller and its components
	explicit AUnitAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the controller is first initialized
	virtual void BeginPlay() override;

public:
	// Returns the AI StateTree component driving this unit's behavior
	UFUNCTION(BlueprintCallable, Category = "AI")
	UUnitStateTreeAIComponent* GetUnitStateTreeAIComponent() const;

private:
	// Reference to the custom AI StateTree component (non-editable in Blueprint)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUnitStateTreeAIComponent> UnitStateTreeAIComponent;
};
