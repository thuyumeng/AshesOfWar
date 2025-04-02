// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/Nodes/AResourceNode.h"

// Sets default values
AAResourceNode::AAResourceNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAResourceNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAResourceNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

