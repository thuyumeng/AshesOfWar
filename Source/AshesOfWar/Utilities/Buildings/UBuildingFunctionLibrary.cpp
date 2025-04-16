#include "UBuildingFunctionLibrary.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "Internationalization/Text.h"

// Convertit une map de coût en un texte lisible pour l'UI (ex. : 100 Aetherium, 50 Vitae)
FText UBuildingFunctionLibrary::GetBuildingCostAsText(const TMap<EResourceType, int32>& ResourceCost)
{
	// Étape 1 : Créer une liste de chaînes (ex. : "100 Aetherium")
	// Étape 2 : Itérer sur la TMap
	// Étape 3 : Concaténer chaque coût dans une seule string avec des virgules ou des sauts de ligne
	// Étape 4 : Retourner le résultat avec FText::FromString
	return FText::FromString(TEXT("")); // Placeholder
}

// Vérifie si une zone donnée est libre pour poser un bâtiment
bool UBuildingFunctionLibrary::CanPlaceBuildingHere(UWorld* World, const FVector& Location, const FVector& BoxExtent)
{
	if (!World) return false;

	// Étape 1 : Effectuer un SweepTestByChannel ou Overlap pour vérifier obstacles
	// Étape 2 : Exclure les fantômes/ghosts ou objets non-bloquants
	// Étape 3 : Retourner true si pas d'obstacle bloquant trouvé
	return true; // Placeholder
}
