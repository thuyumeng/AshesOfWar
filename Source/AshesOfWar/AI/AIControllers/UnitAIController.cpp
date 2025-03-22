// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitAIController.h"
#include "AshesOfWar/Unit/Unit.h"



// Sets default values
AUnitAIController::AUnitAIController(const FObjectInitializer& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// load the default behavior tree
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> DefaultBehaviorTree(TEXT("/Referencto_DefaultBehaviorTree"));
	if (DefaultBehaviorTree.Succeeded())
	{
		BehaviorTree = DefaultBehaviorTree.Object;
	}
}

void AUnitAIController::SetBehaviorTreeActive(bool bIsActive)
{
	if (UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent))
	{
		if (bIsActive)
		{
			BehaviorTreeComponent->StartTree(*BehaviorTree);
		}
		else
		{
			BehaviorTreeComponent->StopTree();
		}
	}
}

// Called when the game starts or when spawned
void AUnitAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUnitAIController::OnPossess(APawn* InPawn)
{
	// Create the blackboard component and run the behavior tree
	Super::OnPossess(InPawn);
	// initialize the blackboard
	UBlackboardComponent* BlackboardComponent;
	UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);

	// run the behavior tree
	RunBehaviorTree(BehaviorTree);
}
