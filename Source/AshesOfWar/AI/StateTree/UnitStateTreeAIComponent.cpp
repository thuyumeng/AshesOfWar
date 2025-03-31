// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitStateTreeAIComponent.h"


// Sets default values for this component's properties
UUnitStateTreeAIComponent::UUnitStateTreeAIComponent()
{
	// PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UUnitStateTreeAIComponent::BeginPlay()
{
	Super::BeginPlay();
	StartLogic();
}

void UUnitStateTreeAIComponent::SetStateTree(UStateTree* NewStateTree)
{
	StateTreeRef.SetStateTree(NewStateTree);
	InitializeComponent();
}


