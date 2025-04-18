#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITypes.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "BaseMinerToResourceTask.generated.h"

// Forward declaration to avoid including heavy headers
class AUnitAIController;

/**
 * UBaseMinerToResourceTask
 * 
 * Custom StateTree Task to handle miner AI movement toward either a resource node or a deposit building.
 */
UCLASS()
class ASHESOFWAR_API UBaseMinerToResourceTask : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	// Constructor - Sets default values
	UBaseMinerToResourceTask();

protected:
	/** 
	 * Callback when a MoveTo request completes. 
	 * Handles success or failure of reaching the target.
	 */
	UFUNCTION(BlueprintCallable)
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

	/**
	 * Handles movement logic based on whether the miner is gathering resources or depositing them.
	 */
	void MoveToCurrentTarget();

	/**
	 * Called when the StateTree state is entered.
	 * Responsible for setting up the MoveCompleted delegate and starting the move command.
	 */
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

private:
	/** 
	 * AI Controller managing the miner unit.
	 * Must be assigned via StateTree context.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Context", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AUnitAIController> AIController;
};
