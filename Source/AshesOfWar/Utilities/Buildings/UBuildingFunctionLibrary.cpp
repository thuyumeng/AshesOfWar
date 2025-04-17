#include "UBuildingFunctionLibrary.h"
#include "Internationalization/Text.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

FText UBuildingFunctionLibrary::GetBuildingCostAsText(const TMap<EResourceType, int32>& ResourceCost)
{
	TArray<FString> Parts;

	for (const TPair<EResourceType, int32>& Pair : ResourceCost)
	{
		if (Pair.Value > 0)
		{
			// Convert enum value to readable text
			const FString ResourceName = UEnum::GetDisplayValueAsText(Pair.Key).ToString();
			Parts.Add(FString::Printf(TEXT("%d %s"), Pair.Value, *ResourceName));
		}
	}

	const FString FinalString = FString::Join(Parts, TEXT(", "));
	return FText::FromString(FinalString);
}

bool UBuildingFunctionLibrary::CanPlaceBuildingHere(UWorld* World, const FVector& Location, const FVector& BoxExtent)
{
	if (!World)
	{
		return false;
	}

	// Create collision shape for sweep
	FCollisionShape CollisionShape = FCollisionShape::MakeBox(BoxExtent);
	FCollisionQueryParams Params;
	Params.bTraceComplex = false;
	Params.bReturnPhysicalMaterial = false;

	// Perform a simple collision check (static objects only)
	const bool bHitObstacle = World->SweepTestByChannel(
		Location,
		Location,
		FQuat::Identity,
		ECC_WorldStatic,
		CollisionShape,
		Params
	);

	// Optional debug visualization
	// DrawDebugBox(World, Location, BoxExtent, FColor::Cyan, false, 1.0f);

	return !bHitObstacle;
}
