// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitAIController.h"
#include "AshesOfWar/AI/StateTree/UnitStateTreeAIComponent.h"



// Sets default values
AUnitAIController::AUnitAIController(const FObjectInitializer& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UnitStateTreeAIComponent = CreateDefaultSubobject<UUnitStateTreeAIComponent>(TEXT("UnitStateTreeAI"));
}


// Called when the game starts or when spawned
void AUnitAIController::BeginPlay()
{
	Super::BeginPlay();
	
}