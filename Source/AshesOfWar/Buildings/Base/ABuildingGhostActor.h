#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABuildingGhostActor.generated.h"

// Forward declarations to reduce unnecessary includes
class UStaticMeshComponent;
class UMaterialInstanceDynamic;

/**
 * ABuildingGhostActor
 *
 * Temporary visual actor used to preview building placement in RTS-style gameplay.
 */
UCLASS()
class ASHESOFWAR_API ABuildingGhostActor : public AActor
{
	GENERATED_BODY()

public:
	// Constructor
	ABuildingGhostActor();

	/**
	 * Updates the ghost actor's world location based on the mouse cursor.
	 * Performs a raycast under the mouse to find a valid ground position.
	 */
	void UpdateLocationFromMouse();

	/**
	 * Updates the ghost actor's material color based on whether the placement is valid.
	 * Green for valid placement, red for invalid placement.
	 */
	void SetValidPlacement(bool bIsValid);

	/**
	 * Sets the static mesh to be used for previewing the building.
	 */
	void SetPreviewMesh(UStaticMesh* MeshToPreview);

private:
	/** 
	 * Visual static mesh component for the ghost actor.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* PreviewMesh;

	/**
	 * Dynamic material instance used to change the ghost's color during placement.
	 */
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;
};
