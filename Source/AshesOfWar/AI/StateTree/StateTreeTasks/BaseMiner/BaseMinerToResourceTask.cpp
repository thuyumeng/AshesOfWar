#include "BaseMinerToResourceTask.h"
#include "AshesOfWar/AI/AIControllers/UnitAIController.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"
#include "Kismet/GameplayStatics.h"
#include "StateTreeExecutionContext.h"
#include "Navigation/PathFollowingComponent.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"
#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"

UBaseMinerToResourceTask::UBaseMinerToResourceTask()
	: UStateTreeTaskBlueprintBase(FObjectInitializer::Get())
{
}

void UBaseMinerToResourceTask::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (Result == EPathFollowingResult::Success)
	{
		FinishTask(true);
	}
	else
	{
		FinishTask(false);
		UE_LOG(LogTemp, Warning, TEXT("Move to Target failed"));
	}
}

void UBaseMinerToResourceTask::MoveToCurrentTarget()
{
	if (!AIController) return;

	AMiner* ControlledMiner = Cast<AMiner>(AIController->GetPawn());
	if (!ControlledMiner)
	{
		UE_LOG(LogTemp, Error, TEXT("No Miner pawn found in BaseMinerToResourceTask"));
		return;
	}

	if (ControlledMiner->IsDepositing())
	{
		// Mode dépôt ➔ Move vers base
		AActor* TargetBase = ControlledMiner->GetCurrentDepositTarget();
		if (TargetBase)
		{
			AIController->MoveToActor(TargetBase);
		}
	}
	else
	{
		// Mode mining ➔ Move vers minerai
		AActor* TargetNode = ControlledMiner->GetCurrentResourceTarget();
		if (TargetNode)
		{
			AIController->MoveToActor(TargetNode);
		}
	}
}

EStateTreeRunStatus UBaseMinerToResourceTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	if (AIController)
	{
		AIController->ReceiveMoveCompleted.AddUniqueDynamic(this, &UBaseMinerToResourceTask::OnMoveCompleted);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AIController is not initialized: BaseMinerToResourceTask"));
		return EStateTreeRunStatus::Failed;
	}

	MoveToCurrentTarget();
	return Super::EnterState(Context, Transition);
}
