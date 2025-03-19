// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h" 
#include "GameFramework/SpringArmComponent.h"
#include "ARTSCameraManager.generated.h"

/**
 * RTS Camera Manager class.
 * - Handles camera movement using directional keys.
 * - Supports zooming with the mouse wheel.
 * - Allows vertical movement with specified keys.
 */
UCLASS()
class ASHESOFWAR_API AARTSCameraManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AARTSCameraManager();

protected:
	// Called once at the start of the game
	virtual void BeginPlay() override;

public:
	// Called every frame to manage camera movement and zoom
	virtual void Tick(float DeltaTime) override;

private:
	// ---- Camera Components ----

	// Main camera component
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* CameraComponent;

	// Spring arm to handle zoom and camera tilt
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArmComponent;

	// Reference to the PlayerController
	APlayerController* PlayerController;

	// ---- Camera Parameters ----

	// Camera movement speed
	float CameraSpeed;

	// Camera zoom speed
	float ZoomSpeed;

	// Minimum and maximum zoom limits
	float MinZoom;
	float MaxZoom;

	// ---- Internal Functions ----

	// Handles camera movement based on user input
	void MoveCamera(float DeltaTime);

	// Handles zooming based on user input
	void ZoomCamera(float AxisValue);
};
