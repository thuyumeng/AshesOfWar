#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RTSCameraTestActor.generated.h"

class UARTSCameraSubsystem;

/**
 * Acteur de test pour le Subsystem de caméra
 */
UCLASS()
class ASHESOFWAR_API ARTSCameraTestActor : public AActor
{
    GENERATED_BODY()

public:
    ARTSCameraTestActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UARTSCameraSubsystem* CameraSubsystem;
};
