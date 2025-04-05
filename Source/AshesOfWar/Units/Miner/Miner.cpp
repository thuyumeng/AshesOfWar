// Fill out your copyright notice in the Description page of Project Settings.


#include "Miner.h"

#include "AshesOfWar/AI/AIControllers/UnitAIController.h"
#include "AshesOfWar/AI/StateTree/UnitStateTreeAIComponent.h"
#include "StateTree.h"


AMiner::AMiner()
{
}

void AMiner::OnBeginPlay_Implementation()
{
	// load the miner's state tree
	TObjectPtr<AUnitAIController> AIController = GetAIController();
	if (AIController)
	{
		if (UUnitStateTreeAIComponent* StateTreeAIComponent = AIController->GetUnitStateTreeAIComponent())
		{
			// load the state tree asset
			TObjectPtr<UStateTree> StateTree = LoadObject<UStateTree>(
				nullptr,
				TEXT("StateTree'/Game/AI/StateTrees/MinerStateTree.MinerStateTree'"));
			if (!StateTree)
			{
				UE_LOG(LogTemp, Error, TEXT("Miner::OnBeginPlay_Implementation: StateTree is null"));
				return;
			}
			StateTreeAIComponent->SetStateTree(StateTree);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Miner::OnBeginPlay_Implementation: StateTreeAIComponent is null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Miner::OnBeginPlay_Implementation: AIController is null"));
	}
}

// Called to bind functionality to input
void AMiner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

