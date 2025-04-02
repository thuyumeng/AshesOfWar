// RTS-style camera subsystem managing movement, zoom, and setup

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ARTSCameraSubsystem.generated.h"

// Forward declarations to reduce compile dependencies
class UCameraComponent;
class USpringArmComponent;
class APlayerController;

/**
 * UARTSCameraSubsystem
 * Subsystem that handles top-down RTS camera logic including movement, zooming, and setup.
 */
UCLASS()
class ASHESOFWAR_API UARTSCameraSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// Constructor
	UARTSCameraSubsystem();

	// Called when the subsystem is initialized
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// Called when the subsystem is deinitialized or the world is unloaded
	virtual void Deinitialize() override;

	// Called every frame to update camera behavior
	void UpdateCamera(float DeltaTime);

	// Accessor to the managed camera component
	UCameraComponent* GetCameraComponent() const;

private:
	// The actual camera used in the world
	UPROPERTY()
	UCameraComponent* CameraComponent;

	// Spring arm component used for positioning and zooming the camera
	UPROPERTY()
	USpringArmComponent* SpringArmComponent;

	// Reference to the player controller owning the camera
	UPROPERTY()
	APlayerController* PlayerController;

	// Camera behavior parameters
	float CameraSpeed;
	float ZoomSpeed;
	float MinZoom;
	float MaxZoom;

	// Internal helper functions
	void TryRetrievePlayerController(); // Called if controller is not available on Init
	void ConfigureCamera();             // Creates and configures camera and spring arm
	void MoveCamera(float DeltaTime);   // Handles WASD movement
	void ZoomCamera(float AxisValue);   // Handles mouse wheel zoom
};
