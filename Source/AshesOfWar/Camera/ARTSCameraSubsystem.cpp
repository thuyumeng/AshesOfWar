#include "ARTSCameraSubsystem.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Constructor: initializes default values for camera behavior
UARTSCameraSubsystem::UARTSCameraSubsystem()
    : CameraComponent(nullptr),
      SpringArmComponent(nullptr),
      PlayerController(nullptr),
      CameraSpeed(2000.0f),
      ZoomSpeed(100.0f),
      MinZoom(500.0f),
      MaxZoom(3000.0f)
{
}

// Called once when the world is initialized
void UARTSCameraSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to retrieve World in Subsystem"));
        return;
    }

    // Try to immediately get the PlayerController
    PlayerController = World->GetFirstPlayerController();
    if (!PlayerController)
    {
        // Retry after a short delay if the controller isn't ready yet
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not found, retrying after delay..."));
        FTimerHandle TimerHandle;
        World->GetTimerManager().SetTimer(TimerHandle, this, &UARTSCameraSubsystem::TryRetrievePlayerController, 1.0f, false);
        return;
    }

    ConfigureCamera();
}

// Retry method to get the PlayerController if it's not available immediately
void UARTSCameraSubsystem::TryRetrievePlayerController()
{
    UWorld* World = GetWorld();
    if (!World) return;

    PlayerController = World->GetFirstPlayerController();
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to retrieve PlayerController after delay."));
        return;
    }

    ConfigureCamera();
}

// Creates and sets up the camera and spring arm for RTS-style control
void UARTSCameraSubsystem::ConfigureCamera()
{
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Error, TEXT("Cannot configure camera: PlayerController missing."));
        return;
    }

    AActor* CameraOwner = PlayerController->GetPawn(); // Prefer pawn if available
    if (!CameraOwner)
    {
        CameraOwner = PlayerController; // Fallback to the controller
    }

    if (!CameraOwner)
    {
        UE_LOG(LogTemp, Error, TEXT("Cannot attach camera: No valid owner found."));
        return;
    }

    // Dynamically create spring arm and camera components
    SpringArmComponent = NewObject<USpringArmComponent>(CameraOwner);
    CameraComponent = NewObject<UCameraComponent>(CameraOwner);

    if (!SpringArmComponent || !CameraComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create camera components"));
        return;
    }

    // Attach the camera setup to the actor
    SpringArmComponent->SetupAttachment(CameraOwner->GetRootComponent());
    CameraComponent->SetupAttachment(SpringArmComponent);

    // Register the components with the engine
    SpringArmComponent->RegisterComponent();
    CameraComponent->RegisterComponent();

    // Set up spring arm defaults
    SpringArmComponent->TargetArmLength = 2500.0f;
    SpringArmComponent->bDoCollisionTest = false;
    SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));

    // Set this camera as the main view target
    PlayerController->SetViewTargetWithBlend(CameraOwner);

    // Setup player input mode and mouse options
    PlayerController->SetInputMode(FInputModeGameOnly());
    PlayerController->bEnableClickEvents = true;
    PlayerController->bEnableMouseOverEvents = true;
    PlayerController->bShowMouseCursor = true;
}

// Called every frame by the game loop (manually invoked)
void UARTSCameraSubsystem::UpdateCamera(float DeltaTime)
{
    if (!CameraComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("CameraComponent not initialized!"));
        return;
    }

    MoveCamera(DeltaTime);

    // Get scroll wheel input and apply zoom
    if (PlayerController)
    {
        float ScrollValue = PlayerController->GetInputAnalogKeyState(EKeys::MouseWheelAxis);
        ZoomCamera(ScrollValue);
    }
}

// Handles WASD movement in the world based on camera direction
void UARTSCameraSubsystem::MoveCamera(float DeltaTime)
{
    if (!PlayerController || !CameraComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerController or CameraComponent unavailable for camera movement"));
        return;
    }

    FVector MoveDirection = FVector::ZeroVector;

    // Project camera direction onto XY plane (avoid vertical movement)
    FVector CameraForward = FVector(CameraComponent->GetForwardVector().X, CameraComponent->GetForwardVector().Y, 0).GetSafeNormal();
    FVector CameraRight = FVector(CameraComponent->GetRightVector().X, CameraComponent->GetRightVector().Y, 0).GetSafeNormal();

    // Detect movement input
    if (PlayerController->IsInputKeyDown(EKeys::W)) MoveDirection += CameraForward;
    if (PlayerController->IsInputKeyDown(EKeys::S)) MoveDirection -= CameraForward;
    if (PlayerController->IsInputKeyDown(EKeys::A)) MoveDirection -= CameraRight;
    if (PlayerController->IsInputKeyDown(EKeys::D)) MoveDirection += CameraRight;

    // Apply camera movement
    if (!MoveDirection.IsNearlyZero())
    {
        FVector NewLocation = CameraComponent->GetOwner()->GetActorLocation() + (MoveDirection * CameraSpeed * DeltaTime);
        CameraComponent->GetOwner()->SetActorLocation(NewLocation);
    }
}

// Zooms the camera in/out based on mouse scroll input
void UARTSCameraSubsystem::ZoomCamera(float AxisValue)
{
    if (FMath::Abs(AxisValue) > KINDA_SMALL_NUMBER)
    {
        float ZoomStep = AxisValue * ZoomSpeed;
        float NewZoom = SpringArmComponent->TargetArmLength - ZoomStep;
        SpringArmComponent->TargetArmLength = FMath::Clamp(NewZoom, MinZoom, MaxZoom);
    }
}

// Returns the current camera component (used for access in other systems)
UCameraComponent* UARTSCameraSubsystem::GetCameraComponent() const
{
    return CameraComponent;
}

// Cleans up and unregisters the camera components when the subsystem is shut down
void UARTSCameraSubsystem::Deinitialize()
{
    if (CameraComponent)
    {
        CameraComponent->DestroyComponent();
        CameraComponent = nullptr;
    }

    if (SpringArmComponent)
    {
        SpringArmComponent->DestroyComponent();
        SpringArmComponent = nullptr;
    }

    PlayerController = nullptr;

    Super::Deinitialize();
}
