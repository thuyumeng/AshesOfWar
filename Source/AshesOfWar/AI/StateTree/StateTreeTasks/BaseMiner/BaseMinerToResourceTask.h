// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITypes.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "BaseMinerToResourceTask.generated.h"

/**
 * 
 */
class AUnitAIController;
UCLASS()
class ASHESOFWAR_API UBaseMinerToResourceTask : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	UBaseMinerToResourceTask();
protected:
	// Move completed callback
	UFUNCTION(BlueprintCallable)
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);
	// Find the nearest resource and move to it
	void MoveToNearestResource();
	// the functions that are called when the task is entered state
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
private:
	// the miner that is going to the resource
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Context", meta=(AllowPrivateAccess=true))
	TObjectPtr<AUnitAIController> AIController;
};
