#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h" // <-- AJOUT ICI
#include "UBuildingFunctionLibrary.generated.h"


UCLASS()
class ASHESOFWAR_API UBuildingFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Retourne une version simplifiée du coût sous forme de texte
	UFUNCTION(BlueprintPure, Category = "Building")
	static FText GetBuildingCostAsText(const TMap<EResourceType, int32>& ResourceCost);

	// Vérifie si un bâtiment peut être placé à une certaine position
	UFUNCTION(BlueprintPure, Category = "Building")
	static bool CanPlaceBuildingHere(UWorld* World, const FVector& Location, const FVector& BoxExtent);
};