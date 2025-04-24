#include "AGameMode_TestRTS.h"
#include "AshesOfWar/Camera/ARTSCameraSubsystem.h"
#include "AshesOfWar/Core/PlayerControllers/ARTSPlayerController.h"
#include "AshesOfWar/Core/GameStates/ARTSGameState.h"

AAGameMode_TestRTS::AAGameMode_TestRTS()
{
	// Définir les classes par défaut
	PlayerControllerClass = ARTSPlayerController::StaticClass();
	GameStateClass = AARTSGameState::StaticClass();
	DefaultPawnClass = nullptr; // Caméra gérée par subsystem
}

void AAGameMode_TestRTS::BeginPlay()
{
	Super::BeginPlay();

	// Activer manuellement le camera subsystem s’il existe
	if (GetWorld())
	{
		if (UARTSCameraSubsystem* CamSubsystem = GetWorld()->GetSubsystem<UARTSCameraSubsystem>())
		{
			UE_LOG(LogTemp, Warning, TEXT("✅ Subsystem Caméra trouvé et activé (via GameMode)"));
			CamSubsystem->UpdateCamera(0.0f); // Appel initial facultatif
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("❌ Subsystem Caméra non trouvé"));
		}
	}
}
