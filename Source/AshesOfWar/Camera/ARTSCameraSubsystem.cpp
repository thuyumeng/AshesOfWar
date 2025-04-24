#include "ARTSCameraSubsystem.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Constructor: initialise les valeurs par défaut
UARTSCameraSubsystem::UARTSCameraSubsystem()
	: CameraComponent(nullptr),
	  SpringArmComponent(nullptr),
	  PlayerController(nullptr),
	  CameraActor(nullptr),
	  CameraSpeed(2000.0f),
	  ZoomSpeed(100.0f),
	  MinZoom(500.0f),
	  MaxZoom(3000.0f)
{
}

// Initialisation au lancement du monde
void UARTSCameraSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to retrieve World in Subsystem"));
		return;
	}

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

// Retente de récupérer le contrôleur joueur
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

// Configuration de la caméra et attachement à un acteur dédié
void UARTSCameraSubsystem::ConfigureCamera()
{
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot configure camera: PlayerController missing."));
		return;
	}

	//*Spawne un acteur vide pour supporter la caméra (si non déjà là)*//
	CameraActor = GetWorld()->SpawnActor<AActor>();
	if (!CameraActor)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn CameraActor."));
		return;
	}

	//*Crée le SpringArm et la Camera et les attache au CameraActor*//
	SpringArmComponent = NewObject<USpringArmComponent>(CameraActor);
	CameraComponent = NewObject<UCameraComponent>(CameraActor);

	if (!SpringArmComponent || !CameraComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create camera components"));
		return;
	}

	//*Assure que l’acteur a un RootComponent*//
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

// Mise à jour de la caméra
void UARTSCameraSubsystem::UpdateCamera(float DeltaTime)
{
	if (!CameraComponent)
	{
		if (!bHasLoggedCameraWarning)
		{
			UE_LOG(LogTemp, Error, TEXT("❌ CameraComponent not initialized!"));
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

// Mouvement WASD
void UARTSCameraSubsystem::MoveCamera(float DeltaTime)
{
	if (!PlayerController || !CameraComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController or CameraComponent unavailable for camera movement"));
		return;
	}

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

// Zoom
void UARTSCameraSubsystem::ZoomCamera(float AxisValue)
{
	if (FMath::Abs(AxisValue) > KINDA_SMALL_NUMBER)
	{
		float ZoomStep = AxisValue * ZoomSpeed;
		float NewZoom = SpringArmComponent->TargetArmLength - ZoomStep;
		SpringArmComponent->TargetArmLength = FMath::Clamp(NewZoom, MinZoom, MaxZoom);
	}
}

// Getter pour la caméra
UCameraComponent* UARTSCameraSubsystem::GetCameraComponent() const
{
	return CameraComponent;
}

// Nettoyage
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
