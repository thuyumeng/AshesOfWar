// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMinerToResourceTask.h"
#include "AshesOfWar/Units/Ore/Ore.h"
#include "AshesOfWar/AI/AIControllers/UnitAIController.h"
#include "AshesOfWar/Units/Miner/Miner.h"
#include "Kismet/GameplayStatics.h"
#include "StateTreeExecutionContext.h"
#include "Navigation/PathFollowingComponent.h"


UBaseMinerToResourceTask::UBaseMinerToResourceTask()
	: UStateTreeTaskBlueprintBase(FObjectInitializer::Get())
{
}

void UBaseMinerToResourceTask::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (Result == EPathFollowingResult::Success)
	{
		// Move was successful, transit to collecting state
		FinishTask(true);
	}
	else
	{
		// Move failed, handle the failure
		FinishTask(false);
		UE_LOG(LogTemp, Warning, TEXT("Move to resource failed"));
	}
}

void UBaseMinerToResourceTask::MoveToNearestResource()
{
	if (AIController)
	{
		// bind the OnMoveCompleted function to the AI controller
		AIController->ReceiveMoveCompleted.AddDynamic(
			this, &UBaseMinerToResourceTask::OnMoveCompleted);
		// find the nearest resource
		TArray<AActor*> Resources;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOre::StaticClass(), Resources);
		if (Resources.Num() > 0)
		{
			// move to the nearest resource
			AIController->MoveToActor(Resources[0]);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AIController is not initialized: BaseMinerToResourceTask"));
	}
}

EStateTreeRunStatus UBaseMinerToResourceTask::EnterState(FStateTreeExecutionContext& Context,
                                                         const FStateTreeTransitionResult& Transition)
{
	// find the nearest resource and move to it
	MoveToNearestResource();
	return Super::EnterState(Context, Transition);
}
