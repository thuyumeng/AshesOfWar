#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AGameMode_TestRTS.generated.h"

/**
 * GameMode de test pour RTS, active la caméra subsystem automatiquement
 */
UCLASS()
class ASHESOFWAR_API AAGameMode_TestRTS : public AGameMode
{
	GENERATED_BODY()

public:
	AAGameMode_TestRTS();

protected:
	virtual void BeginPlay() override;
};
