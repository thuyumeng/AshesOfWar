#include "ABuildingGhostActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

ABuildingGhostActor::ABuildingGhostActor()
{
	// Disable ticking for performance (not needed unless animation required)
	PrimaryActorTick.bCanEverTick = false;

	// Create the preview mesh component
	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewMesh"));
	RootComponent = PreviewMesh;

	// Disable collision for the ghost actor (manual validation handled elsewhere)
	PreviewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PreviewMesh->SetGenerateOverlapEvents(false);
	PreviewMesh->SetCanEverAffectNavigation(false);

	// Dynamic material will be initialized when first needed
	DynamicMaterial = nullptr;
}

void ABuildingGhostActor::UpdateLocationFromMouse()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController) return;

	// Raycast from the mouse cursor onto the world (collision with WorldStatic/Visible objects)
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, HitResult);

	if (HitResult.bBlockingHit)
	{
		// Move the ghost actor to the hit location
		SetActorLocation(HitResult.ImpactPoint);
	}
}

void ABuildingGhostActor::SetValidPlacement(bool bIsValid)
{
	if (!PreviewMesh) return;

	// Create the dynamic material instance if it hasn't been created yet
	if (!DynamicMaterial)
	{
		DynamicMaterial = PreviewMesh->CreateAndSetMaterialInstanceDynamic(0);
	}

	if (DynamicMaterial)
	{
		// Choose color: pale green for valid placement, red for invalid
		const FLinearColor PlacementColor = bIsValid ? FLinearColor(0.5f, 1.0f, 0.5f, 1.0f) : FLinearColor::Red;
		DynamicMaterial->SetVectorParameterValue(FName("Color"), PlacementColor);
	}
}

void ABuildingGhostActor::SetPreviewMesh(UStaticMesh* MeshToPreview)
{
	if (!PreviewMesh || !MeshToPreview) return;

	PreviewMesh->SetStaticMesh(MeshToPreview);

	// Optional: you can set a custom scale here if needed
	// PreviewMesh->SetWorldScale3D(FVector(1.0f));

	// ⚠️ Important: Ensure that the material used has a vector parameter named "Color"
	// so SetValidPlacement() can dynamically modify its tint.
}
