// RTS-style camera subsystem managing movement, zoom, and setup

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ARTSCameraSubsystem.generated.h"

// Forward declarations to reduce compile dependencies
class UCameraComponent;
class USpringArmComponent;
class APlayerController;

/**
 * UARTSCameraSubsystem
 * Subsystem that handles top-down RTS camera logic including movement, zooming, and setup.
 */
UCLASS()
class ASHESOFWAR_API UARTSCameraSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// Constructor
	UARTSCameraSubsystem();

	// Called when the subsystem is initialized
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// Called when the subsystem is deinitialized or the world is unloaded
	virtual void Deinitialize() override;

	// Called every frame to update camera behavior
	void UpdateCamera(float DeltaTime);

	// Accessor to the managed camera component
	UCameraComponent* GetCameraComponent() const;

private:
	// La caméra utilisée dans le monde
	UPROPERTY()
	UCameraComponent* CameraComponent;

	// Spring arm qui supporte la caméra (pour le zoom et la hauteur)
	UPROPERTY()
	USpringArmComponent* SpringArmComponent;

	// Contrôleur joueur pour la caméra
	UPROPERTY()
	APlayerController* PlayerController;

	// Référence à l’acteur physique qui contient la caméra (ex: un AActor vide)
	UPROPERTY()
	AActor* CameraActor;

	// Paramètres de la caméra
	float CameraSpeed;
	float ZoomSpeed;
	float MinZoom;
	float MaxZoom;

	bool bHasLoggedCameraWarning = false;

	// Fonctions internes
	void TryRetrievePlayerController(); // Si le controller n’est pas dispo immédiatement
	void ConfigureCamera();             // Crée les composants et les attache
	void MoveCamera(float DeltaTime);   // Déplacement (WASD)
	void ZoomCamera(float AxisValue);   // Zoom (roulette souris)
};
