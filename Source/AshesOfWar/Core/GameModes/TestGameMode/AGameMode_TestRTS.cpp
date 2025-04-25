#include "AGameMode_TestRTS.h"
#include "AshesOfWar/Camera/ARTSCameraSubsystem.h"
#include "AshesOfWar/Core/PlayerControllers/ARTSPlayerController.h"
#include "AshesOfWar/Core/GameStates/ARTSGameState.h"

// --- Constructor ---
AAGameMode_TestRTS::AAGameMode_TestRTS()
{
	// Setup default RTS gameplay classes
	PlayerControllerClass = ARTSPlayerController::StaticClass();
	GameStateClass = AARTSGameState::StaticClass();
	DefaultPawnClass = nullptr; // RTS camera handled by subsystem
}

// --- BeginPlay: initialize camera subsystem ---
void AAGameMode_TestRTS::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		if (UARTSCameraSubsystem* CamSubsystem = World->GetSubsystem<UARTSCameraSubsystem>())
		{
			CamSubsystem->UpdateCamera(0.0f); // Optional: trigger initial camera update
			UE_LOG(LogTemp, Log, TEXT("[GameMode] ✅ Camera subsystem initialized via GameMode."));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[GameMode] ❌ Camera subsystem not found."));
		}
	}
}
