#pragma once

// --- Includes ---
#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitAIController.generated.h"

// --- Forward Declarations ---
class UUnitStateTreeAIComponent;

/**
 * AUnitAIController
 * 
 * Custom AI Controller for RTS units.
 * Uses a StateTree AI component to manage unit behavior and decision logic.
 */
UCLASS()
class ASHESOFWAR_API AUnitAIController : public AAIController
{
	GENERATED_BODY()

public:
	// --- Constructor ---
	explicit AUnitAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// --- Lifecycle ---
	virtual void BeginPlay() override;

public:
	// --- Getters ---
	UFUNCTION(BlueprintCallable, Category = "AI")
	UUnitStateTreeAIComponent* GetUnitStateTreeAIComponent() const;

private:
	// --- Components ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUnitStateTreeAIComponent> UnitStateTreeAIComponent;
};
