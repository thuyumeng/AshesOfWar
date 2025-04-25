#pragma once

// --- Includes ---
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ARTSCameraSubsystem.generated.h"

// --- Forward Declarations ---
class UCameraComponent;
class USpringArmComponent;
class APlayerController;

/**
 * UARTSCameraSubsystem
 * 
 * Subsystem that manages top-down RTS camera behavior:
 * - Automatic setup on startup
 * - WASD movement and mouse-wheel zoom
 * - Centralized handling of camera actor, spring arm and camera component
 */
UCLASS()
class ASHESOFWAR_API UARTSCameraSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// --- Constructor ---
	UARTSCameraSubsystem();

	// --- Subsystem Lifecycle ---
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// --- Runtime Updates ---
	/** Updates camera position and zoom based on player input. Called every frame. */
	void UpdateCamera(float DeltaTime);

	// --- Accessors ---
	/** Returns the RTS camera component used in the subsystem. */
	UCameraComponent* GetCameraComponent() const;

private:
	// --- Core References ---
	UPROPERTY()
	UCameraComponent* CameraComponent;

	UPROPERTY()
	USpringArmComponent* SpringArmComponent;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	AActor* CameraActor;

	// --- Camera Parameters ---
	float CameraSpeed;
	float ZoomSpeed;
	float MinZoom;
	float MaxZoom;

	bool bHasLoggedCameraWarning = false;

	// --- Internal Logic ---
	/** Attempts to retrieve the PlayerController if not immediately available. */
	void TryRetrievePlayerController();

	/** Configures and spawns the camera actor, spring arm, and camera. */
	void ConfigureCamera();

	/** Moves the camera actor based on WASD inputs. */
	void MoveCamera(float DeltaTime);

	/** Zooms the camera in or out based on mouse wheel input. */
	void ZoomCamera(float AxisValue);
};
