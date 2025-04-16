#include "UBuildingFunctionLibrary.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "Internationalization/Text.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

// Convertit une map de coût en un texte lisible pour l'UI (ex. : "100 Aetherium, 50 Vitae")
FText UBuildingFunctionLibrary::GetBuildingCostAsText(const TMap<EResourceType, int32>& ResourceCost)
{
	TArray<FString> Parts;

	for (const TPair<EResourceType, int32>& Pair : ResourceCost)
	{
		if (Pair.Value > 0)
		{
			const FString ResourceName = UEnum::GetDisplayValueAsText(Pair.Key).ToString(); // "Aetherium"
			Parts.Add(FString::Printf(TEXT("%d %s"), Pair.Value, *ResourceName));
		}
	}

	FString FinalString = FString::Join(Parts, TEXT(", "));
	return FText::FromString(FinalString);
}

// Vérifie si une zone donnée est libre pour poser un bâtiment (box collision)
bool UBuildingFunctionLibrary::CanPlaceBuildingHere(UWorld* World, const FVector& Location, const FVector& BoxExtent)
{
	if (!World) return false;

	FCollisionShape CollisionShape = FCollisionShape::MakeBox(BoxExtent);
	FCollisionQueryParams Params;
	Params.bTraceComplex = false;
	Params.bReturnPhysicalMaterial = false;

	// Ici on pourrait ajouter un tag ou ignorer certains acteurs (ghosts par exemple)

	// Effectue un test de collision statique
	bool bHitObstacle = World->SweepTestByChannel(
		Location,
		Location,
		FQuat::Identity,
		ECC_WorldStatic,
		CollisionShape,
		Params
	);

	// Optionnel : Affiche une box debug pendant 1 sec
	// DrawDebugBox(World, Location, BoxExtent, FColor::Cyan, false, 1.f);

	return !bHitObstacle;
}
