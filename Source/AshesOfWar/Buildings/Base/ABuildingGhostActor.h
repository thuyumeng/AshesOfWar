#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABuildingGhostActor.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;

/**
 * Acteur fantôme servant à prévisualiser l’emplacement du bâtiment.
 */
UCLASS()
class ASHESOFWAR_API ABuildingGhostActor : public AActor
{
	GENERATED_BODY()

public:
	// Constructeur
	ABuildingGhostActor();

	// Met à jour la position du ghost selon la souris
	void UpdateLocationFromMouse();

	// Applique une couleur selon la validité du placement
	void SetValidPlacement(bool bIsValid);

	// Applique le mesh du bâtiment à prévisualiser
	void SetPreviewMesh(UStaticMesh* MeshToPreview);

private:
	// Composant visuel du bâtiment fantôme
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* PreviewMesh;

	// Matériau dynamique utilisé pour le feedback visuel
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;
};
