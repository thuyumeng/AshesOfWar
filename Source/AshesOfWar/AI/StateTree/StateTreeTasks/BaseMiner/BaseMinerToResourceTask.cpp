#include "BaseMinerToResourceTask.h"
#include "AshesOfWar/AI/AIControllers/UnitAIController.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"
#include "StateTreeExecutionContext.h"
#include "Navigation/PathFollowingComponent.h"


UBaseMinerToResourceTask::UBaseMinerToResourceTask()
	: UStateTreeTaskBlueprintBase(FObjectInitializer::Get())
{
	// Constructor body (empty for now)
}

void UBaseMinerToResourceTask::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("Miner reached target. Result = %d (Success = %d)"), (int32)Result, (int32)EPathFollowingResult::Success);
	

	if (Result == EPathFollowingResult::Success)
	{
		// Successfully reached the target - finish the task successfully
		FinishTask(true);
	}
	else
	{
		// Failed to reach the target - fail the task
		FinishTask(false);
		UE_LOG(LogTemp, Warning, TEXT("BaseMinerToResourceTask: Failed to move to the target."));
	}
}

void UBaseMinerToResourceTask::MoveToCurrentTarget()
{
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("BaseMinerToResourceTask: AIController is not valid."));
		return;
	}

	// Try to cast the controlled pawn to a Miner
	AMiner* ControlledMiner = Cast<AMiner>(AIController->GetPawn());
	if (!ControlledMiner)
	{
		UE_LOG(LogTemp, Error, TEXT("BaseMinerToResourceTask: Controlled pawn is not a Miner."));
		return;
	}

	// Determine the correct target based on the miner's current action
	if (ControlledMiner->IsDepositing())
	{
		// If depositing, move to the current base
		if (AActor* TargetBase = ControlledMiner->GetCurrentDepositTarget())
		{
			AIController->MoveToActor(TargetBase);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("BaseMinerToResourceTask: No deposit target set."));
		}
	}
	else
	{
		// Otherwise, move to the resource node
		if (AActor* TargetNode = ControlledMiner->GetCurrentResourceTarget())
		{
			AIController->MoveToActor(TargetNode);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("BaseMinerToResourceTask: No resource target set."));
		}
	}
}

EStateTreeRunStatus UBaseMinerToResourceTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	// Validate the AIController reference
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("BaseMinerToResourceTask: AIController is not assigned."));
		return EStateTreeRunStatus::Failed;
	}

	// Register the OnMoveCompleted delegate
	AIController->ReceiveMoveCompleted.AddUniqueDynamic(this, &UBaseMinerToResourceTask::OnMoveCompleted);

	// Start moving toward the appropriate target
	MoveToCurrentTarget();

	return Super::EnterState(Context, Transition);
}