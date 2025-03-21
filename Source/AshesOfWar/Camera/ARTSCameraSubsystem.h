#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ARTSCameraSubsystem.generated.h"

class UCameraComponent;
class USpringArmComponent;
class APlayerController;

/**
 * UARTSCameraSubsystem - Manages the RTS camera as a subsystem.
 */
UCLASS()
class ASHESOFWAR_API UARTSCameraSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    UARTSCameraSubsystem();

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    void UpdateCamera(float DeltaTime);
    UCameraComponent* GetCameraComponent() const;

private:
    UPROPERTY()
    UCameraComponent* CameraComponent; // Camera component

    UPROPERTY()
    USpringArmComponent* SpringArmComponent; // Spring arm for camera movement

    UPROPERTY()
    APlayerController* PlayerController; // Reference to the player controller

    float CameraSpeed; // Movement speed of the camera
    float ZoomSpeed; // Zoom speed
    float MinZoom; // Minimum zoom distance
    float MaxZoom; // Maximum zoom distance

    void TryRetrievePlayerController(); // Attempts to retrieve the player controller
    void ConfigureCamera(); // Sets up the camera system
    void MoveCamera(float DeltaTime); // Handles camera movement
    void ZoomCamera(float AxisValue); // Handles zoom functionality
};
