#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AshesOfWar/Buildings/Base/FBuildingInfo.h"
#include "UBuildingSelectionWidget.generated.h"

/**
 * UBuildingSelectionWidget
 * 
 * Widget responsible for displaying a list of available buildings
 * and allowing players to select one for construction.
 */
UCLASS()
class ASHESOFWAR_API UBuildingSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * Initializes the UI with a list of available buildings.
	 * This method can be called from Blueprint or C++.
	 */
	UFUNCTION(BlueprintCallable, Category = "UI")
	void InitializeBuildingList(const TArray<FBuildingInfo>& AvailableBuildings);

	/**
	 * Called when a player clicks on a building button (implemented via Blueprint).
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnBuildingSelected(FName BuildingID);

protected:
	/** Internal list of buildings currently displayed in the selection menu. */
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TArray<FBuildingInfo> DisplayedBuildings;
};
