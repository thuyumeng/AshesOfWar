#include "RTSCameraTestActor.h"
#include "AshesOfWar/Camera/ARTSCameraSubsystem.h"
#include "Engine/World.h"

ARTSCameraTestActor::ARTSCameraTestActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ARTSCameraTestActor::BeginPlay()
{
    Super::BeginPlay();

    UWorld* World = GetWorld();
    if (World)
    {
        CameraSubsystem = World->GetSubsystem<UARTSCameraSubsystem>();

        if (CameraSubsystem)
        {
            UE_LOG(LogTemp, Warning, TEXT("UARTSCameraSubsystem trou!"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("UARTSCameraSubsystem non trou!"));
        }
    }
}

void ARTSCameraTestActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CameraSubsystem)
    {
        CameraSubsystem->UpdateCamera(DeltaTime);
    }
}

