#pragma once

// --- Includes ---
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AGameMode_TestRTS.generated.h"

/**
 * AAGameMode_TestRTS
 * 
 * Custom GameMode for RTS testing.
 * Automatically sets default controller/state and activates the camera subsystem.
 */
UCLASS()
class ASHESOFWAR_API AAGameMode_TestRTS : public AGameMode
{
	GENERATED_BODY()

public:
	// --- Constructor ---
	AAGameMode_TestRTS();

protected:
	// --- Lifecycle Hook ---
	virtual void BeginPlay() override;
};
