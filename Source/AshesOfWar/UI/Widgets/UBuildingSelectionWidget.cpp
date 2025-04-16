#include "UBuildingSelectionWidget.h"

// Initialise la liste des bâtiments affichables à l'écran
void UBuildingSelectionWidget::InitializeBuildingList(const TArray<FBuildingInfo>& AvailableBuildings)
{
	// Étape 1 : Sauvegarde la liste localement
	DisplayedBuildings = AvailableBuildings;

	// Étape 2 : Nettoie l'UI actuelle (ex. : panel vertical, scroll box, etc.)

	// Étape 3 : Pour chaque FBuildingInfo, créer dynamiquement un widget enfant :
	// - Afficher l'icône du bâtiment
	// - Afficher le nom et le coût
	// - Ajouter un bouton (Bind OnClicked → appelle OnBuildingSelected avec BuildingID)
    
	// ⚠️ À faire depuis le Blueprint ou avec un UVerticalBox dans C++ si tu veux le gérer côté code pur
}
