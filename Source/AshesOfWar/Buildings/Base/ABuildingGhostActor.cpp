#include "ABuildingGhostActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Constructeur du bâtiment fantôme (ghost)
ABuildingGhostActor::ABuildingGhostActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Composant visuel du bâtiment (mesh)
	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewMesh"));
	RootComponent = PreviewMesh;

	// Pas de collisions pour le ghost (on les détecte nous-mêmes)
	PreviewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PreviewMesh->SetGenerateOverlapEvents(false);
	PreviewMesh->SetCanEverAffectNavigation(false);

	// Le matériau dynamique sera créé lors du premier appel à SetValidPlacement()
	DynamicMaterial = nullptr;
}

// Met à jour la position du Ghost en fonction de la souris (RTS-style)
void ABuildingGhostActor::UpdateLocationFromMouse()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return;

	// Raycast depuis la caméra vers le sol (visible ou WorldStatic)
	FHitResult Hit;
	PC->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);

	if (Hit.bBlockingHit)
	{
		// Positionne le bâtiment ghost à l’impact
		SetActorLocation(Hit.ImpactPoint);
	}
}

// Change dynamiquement la couleur du Ghost selon s’il peut être placé ou non
void ABuildingGhostActor::SetValidPlacement(bool bIsValid)
{
	if (!PreviewMesh) return;

	// Crée le matériau dynamique si ce n’est pas encore fait
	if (!DynamicMaterial)
	{
		DynamicMaterial = PreviewMesh->CreateAndSetMaterialInstanceDynamic(0);
	}

	if (DynamicMaterial)
	{
		// Vert pâle si placement valide, rouge sinon
		FLinearColor Color = bIsValid ? FLinearColor(0.5f, 1.f, 0.5f, 1.f) : FLinearColor::Red;
		DynamicMaterial->SetVectorParameterValue(FName("Color"), Color);
	}
}

// Définit le mesh à afficher pour le bâtiment fantôme
void ABuildingGhostActor::SetPreviewMesh(UStaticMesh* MeshToPreview)
{
	if (!PreviewMesh || !MeshToPreview) return;

	PreviewMesh->SetStaticMesh(MeshToPreview);

	// Optionnel : applique une échelle custom
	// PreviewMesh->SetWorldScale3D(FVector(1.f));

	// ⚠️ Assure-toi que le matériau utilisé contient un paramètre vectoriel nommé \"Color\"
	// pour que SetValidPlacement fonctionne correctement
}
