// Fill out your copyright notice in the Description page of Project Settings.


#include "Ore.h"

#include "AshesOfWar/AI/AIControllers/UnitAIController.h"
#include "GameFramework/CharacterMovementComponent.h"


void AOre::OnBeginPlay_Implementation()
{
	// TODO: Do we need to set up a basic class for the ore unit?
	// remove the character movement component
	GetCharacterMovement()->Deactivate();
	// remove the AI controller
	if (AUnitAIController* AIController = Cast<AUnitAIController>(GetController()))
	{
		AIController->StopMovement();
		AIController->Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ore unit has no AI controller!"));
	}
	// remove the skeletal mesh
	GetMesh()->DestroyComponent();
}
