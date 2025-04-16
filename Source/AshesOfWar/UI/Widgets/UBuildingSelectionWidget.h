#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AshesOfWar/Buildings/Base/FBuildingInfo.h"
#include "UBuildingSelectionWidget.generated.h"

UCLASS()
class ASHESOFWAR_API UBuildingSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Initialise l’interface avec une liste de bâtiments disponibles (via Blueprint ou C++)
	UFUNCTION(BlueprintCallable, Category = "UI")
	void InitializeBuildingList(const TArray<FBuildingInfo>& AvailableBuildings);

	// Appelé quand le joueur clique sur un bouton de bâtiment (bind dans Blueprint)
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnBuildingSelected(FName BuildingID);

protected:
	// Liste interne des bâtiments affichés dans le menu
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TArray<FBuildingInfo> DisplayedBuildings;
};