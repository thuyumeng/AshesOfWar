#include "ARTSCameraSubsystem.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"

// --- Constructor ---
UARTSCameraSubsystem::UARTSCameraSubsystem()
	: CameraComponent(nullptr),
	  SpringArmComponent(nullptr),
	  PlayerController(nullptr),
	  CameraActor(nullptr),
	  CameraSpeed(2000.0f),
	  ZoomSpeed(100.0f),
	  MinZoom(500.0f),
	  MaxZoom(3000.0f),
	  bHasLoggedCameraWarning(false)
{
}

// --- Initialization ---
void UARTSCameraSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("[CameraSubsystem] Failed to retrieve world."));
		return;
	}

	PlayerController = World->GetFirstPlayerController();
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("[CameraSubsystem] PlayerController not found. Retrying..."));
		FTimerHandle TimerHandle;
		World->GetTimerManager().SetTimer(TimerHandle, this, &UARTSCameraSubsystem::TryRetrievePlayerController, 1.0f, false);
		return;
	}

	ConfigureCamera();
}

void UARTSCameraSubsystem::TryRetrievePlayerController()
{
	if (UWorld* World = GetWorld())
	{
		PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			ConfigureCamera();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[CameraSubsystem] Failed to retrieve PlayerController on retry."));
		}
	}
}

// --- Camera Setup ---
void UARTSCameraSubsystem::ConfigureCamera()
{
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("[CameraSubsystem] Cannot configure camera: PlayerController missing."));
		return;
	}

	CameraActor = GetWorld()->SpawnActor<AActor>();
	if (!CameraActor)
	{
		UE_LOG(LogTemp, Error, TEXT("[CameraSubsystem] Failed to spawn CameraActor."));
		return;
	}

	SpringArmComponent = NewObject<USpringArmComponent>(CameraActor);
	CameraComponent = NewObject<UCameraComponent>(CameraActor);

	if (!SpringArmComponent || !CameraComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("[CameraSubsystem] Failed to create camera components."));
		return;
	}

	if (!CameraActor->GetRootComponent())
	{
		USceneComponent* Root = NewObject<USceneComponent>(CameraActor);
		CameraActor->SetRootComponent(Root);
		Root->RegisterComponent();
	}

	SpringArmComponent->SetupAttachment(CameraActor->GetRootComponent());
	CameraComponent->SetupAttachment(SpringArmComponent);

	SpringArmComponent->RegisterComponent();
	CameraComponent->RegisterComponent();

	SpringArmComponent->TargetArmLength = 2500.0f;
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));

	PlayerController->SetViewTargetWithBlend(CameraActor);
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bEnableClickEvents = true;
	PlayerController->bEnableMouseOverEvents = true;
	PlayerController->bShowMouseCursor = true;
}

// --- Camera Update ---
void UARTSCameraSubsystem::UpdateCamera(float DeltaTime)
{
	if (!CameraComponent)
	{
		if (!bHasLoggedCameraWarning)
		{
			UE_LOG(LogTemp, Error, TEXT("[CameraSubsystem] ❌ CameraComponent not initialized."));
			bHasLoggedCameraWarning = true;
		}
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
	if (!PlayerController || !CameraComponent) return;

	FVector MoveDirection = FVector::ZeroVector;

	FVector CameraForward = FVector(CameraComponent->GetForwardVector().X, CameraComponent->GetForwardVector().Y, 0).GetSafeNormal();
	FVector CameraRight = FVector(CameraComponent->GetRightVector().X, CameraComponent->GetRightVector().Y, 0).GetSafeNormal();

	if (PlayerController->IsInputKeyDown(EKeys::W)) MoveDirection += CameraForward;
	if (PlayerController->IsInputKeyDown(EKeys::S)) MoveDirection -= CameraForward;
	if (PlayerController->IsInputKeyDown(EKeys::A)) MoveDirection -= CameraRight;
	if (PlayerController->IsInputKeyDown(EKeys::D)) MoveDirection += CameraRight;

	if (!MoveDirection.IsNearlyZero())
	{
		FVector NewLocation = CameraActor->GetActorLocation() + (MoveDirection * CameraSpeed * DeltaTime);
		CameraActor->SetActorLocation(NewLocation);
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

// --- Deinitialization ---
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

	if (CameraActor)
	{
		CameraActor->Destroy();
		CameraActor = nullptr;
	}

	PlayerController = nullptr;

	Super::Deinitialize();
}
