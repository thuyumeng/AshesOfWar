#include "ARTSCameraSubsystem.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TimerManager.h"

UARTSCameraSubsystem::UARTSCameraSubsystem()
    : CameraComponent(nullptr),
    SpringArmComponent(nullptr),
    PlayerController(nullptr),
    CameraSpeed(2000.0f), // Increased for a more responsive movement
    ZoomSpeed(100.0f),
    MinZoom(500.0f),
    MaxZoom(3000.0f)
{
}

void UARTSCameraSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to retrieve World in Subsystem"));
        return;
    }

    // Try retrieving the PlayerController immediately
    PlayerController = World->GetFirstPlayerController();
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not found, retrying after delay..."));
        FTimerHandle TimerHandle;
        World->GetTimerManager().SetTimer(TimerHandle, this, &UARTSCameraSubsystem::TryRetrievePlayerController, 1.0f, false);
        return;
    }

    ConfigureCamera();
}

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

void UARTSCameraSubsystem::ConfigureCamera()
{
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Error, TEXT("Cannot configure camera: PlayerController missing."));
        return;
    }

    // Retrieve the actor that will own the camera
    AActor* CameraOwner = PlayerController->GetPawn();
    if (!CameraOwner)
    {
        CameraOwner = PlayerController; // Fallback to PlayerController itself
    }

    if (!CameraOwner)
    {
        UE_LOG(LogTemp, Error, TEXT("Cannot attach camera: No valid owner found."));
        return;
    }

    // Create camera components
    SpringArmComponent = NewObject<USpringArmComponent>(CameraOwner);
    CameraComponent = NewObject<UCameraComponent>(CameraOwner);

    if (!SpringArmComponent || !CameraComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create camera components"));
        return;
    }

    // Attach camera components
    SpringArmComponent->SetupAttachment(CameraOwner->GetRootComponent());
    CameraComponent->SetupAttachment(SpringArmComponent);

    // Register components
    SpringArmComponent->RegisterComponent();
    CameraComponent->RegisterComponent();

    // Configure spring arm settings
    SpringArmComponent->TargetArmLength = 2500.0f;
    SpringArmComponent->bDoCollisionTest = false;
    SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));

    // Set the camera as the main view target
    PlayerController->SetViewTargetWithBlend(CameraOwner);

    // Enable user input
    PlayerController->SetInputMode(FInputModeGameOnly());
    PlayerController->bEnableClickEvents = true;
    PlayerController->bEnableMouseOverEvents = true;
    PlayerController->bShowMouseCursor = true;
}

void UARTSCameraSubsystem::UpdateCamera(float DeltaTime)
{
    if (!CameraComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("CameraComponent not initialized!"));
        return;
    }

    MoveCamera(DeltaTime);

    if (PlayerController)
    {
        float ScrollValue = PlayerController->GetInputAnalogKeyState(EKeys::MouseWheelAxis);
        ZoomCamera(ScrollValue);
    }
}

void UARTSCameraSubsystem::MoveCamera(float DeltaTime)
{
    if (!PlayerController || !CameraComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerController or CameraComponent unavailable for camera movement"));
        return;
    }

    FVector MoveDirection = FVector::ZeroVector;

    // Projecting the camera forward/right vectors onto the XY plane to prevent unintended vertical movement
    FVector CameraForward = FVector(CameraComponent->GetForwardVector().X, CameraComponent->GetForwardVector().Y, 0).GetSafeNormal();
    FVector CameraRight = FVector(CameraComponent->GetRightVector().X, CameraComponent->GetRightVector().Y, 0).GetSafeNormal();

    // Movement inputs
    if (PlayerController->IsInputKeyDown(EKeys::W))
    {
        MoveDirection += CameraForward;
    }
    if (PlayerController->IsInputKeyDown(EKeys::S))
    {
        MoveDirection -= CameraForward;
    }
    if (PlayerController->IsInputKeyDown(EKeys::A))
    {
        MoveDirection -= CameraRight;
    }
    if (PlayerController->IsInputKeyDown(EKeys::D))
    {
        MoveDirection += CameraRight;
    }

    // Apply movement if input exists
    if (!MoveDirection.IsNearlyZero())
    {
        FVector NewLocation = CameraComponent->GetOwner()->GetActorLocation() + (MoveDirection * CameraSpeed * DeltaTime);
        CameraComponent->GetOwner()->SetActorLocation(NewLocation);
    }
}

void UARTSCameraSubsystem::ZoomCamera(float AxisValue)
{
    if (FMath::Abs(AxisValue) > KINDA_SMALL_NUMBER)
    {
        float ZoomStep = AxisValue * ZoomSpeed;
        float NewZoom = SpringArmComponent->TargetArmLength - ZoomStep;
        SpringArmComponent->TargetArmLength = FMath::Clamp(NewZoom, MinZoom, MaxZoom);
    }
}

UCameraComponent* UARTSCameraSubsystem::GetCameraComponent() const
{
    return CameraComponent;
}

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
