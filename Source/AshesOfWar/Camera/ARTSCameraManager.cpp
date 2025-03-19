// Fill out your copyright notice in the Description page of Project Settings.

#include "ARTSCameraManager.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Constructor: Initializes the camera components and settings
AARTSCameraManager::AARTSCameraManager()
{
	PrimaryActorTick.bCanEverTick = true;

	// Creating and configuring the SpringArm
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	RootComponent = SpringArmComponent;
	SpringArmComponent->TargetArmLength = 1000.0f; // Initial height
	SpringArmComponent->bDoCollisionTest = false;  // Disables collision to prevent obstructions
	SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f)); // Fixed tilt angle

	// Creating and attaching the camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	// Setting camera parameters
	CameraSpeed = 1000.0f;
	ZoomSpeed = 25.0f;
	MinZoom = 300.0f;
	MaxZoom = 2500.0f;
}

// Called once at the start of the game
void AARTSCameraManager::BeginPlay()
{
	Super::BeginPlay();

	// Retrieving the PlayerController
	PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;  // Enables cursor display
		PlayerController->SetViewTarget(this);      // Sets this camera as the main view

		// Enabling user input
		EnableInput(PlayerController);
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}
}

// Called every frame to handle camera movement and zoom
void AARTSCameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle camera movement
	MoveCamera(DeltaTime);

	// Handle zoom via the mouse wheel
	if (PlayerController)
	{
		float ScrollValue = PlayerController->GetInputAnalogKeyState(EKeys::MouseWheelAxis);
		ZoomCamera(ScrollValue);
	}
}

// Handles camera movement using directional keys
void AARTSCameraManager::MoveCamera(float DeltaTime)
{
	if (!PlayerController) return;

	FVector MoveDirection = FVector::ZeroVector;

	// Check which keys are pressed and adjust direction accordingly
	if (PlayerController->IsInputKeyDown(EKeys::W))
	{
		MoveDirection += FVector(1, 0, 0);
	}
	if (PlayerController->IsInputKeyDown(EKeys::S))
	{
		MoveDirection += FVector(-1, 0, 0);
	}
	if (PlayerController->IsInputKeyDown(EKeys::A))
	{
		MoveDirection += FVector(0, -1, 0);
	}
	if (PlayerController->IsInputKeyDown(EKeys::D))
	{
		MoveDirection += FVector(0, 1, 0);
	}

	// Handle vertical movement
	if (PlayerController->IsInputKeyDown(EKeys::SpaceBar))
	{
		MoveDirection += FVector(0, 0, 1);
	}
	if (PlayerController->IsInputKeyDown(EKeys::LeftControl))
	{
		MoveDirection += FVector(0, 0, -1);
	}

	// Apply movement if any key is pressed
	if (!MoveDirection.IsNearlyZero())
	{
		FVector NewLocation = GetActorLocation() + (MoveDirection * CameraSpeed * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

// Handles zooming using the mouse wheel
void AARTSCameraManager::ZoomCamera(float AxisValue)
{
	if (FMath::Abs(AxisValue) > KINDA_SMALL_NUMBER)
	{
		float ZoomStep = AxisValue * ZoomSpeed;
		float NewZoom = SpringArmComponent->TargetArmLength - ZoomStep;

		// Apply zoom limits
		NewZoom = FMath::Clamp(NewZoom, MinZoom, MaxZoom);

		// Update the SpringArm with the new zoom value
		SpringArmComponent->TargetArmLength = NewZoom;
		SpringArmComponent->MarkRenderStateDirty();
	}
}
