#include "UBuildingSelectionWidget.h"

void UBuildingSelectionWidget::InitializeBuildingList(const TArray<FBuildingInfo>& AvailableBuildings)
{
	// Step 1: Save the list locally
	DisplayedBuildings = AvailableBuildings;

	// Step 2: Clear the current UI (e.g., vertical panel, scroll box)
	// Note: Should be handled via Blueprint logic or dynamic widget generation in C++

	// Step 3: For each FBuildingInfo, dynamically create a child widget:
	// - Display building icon
	// - Display building name and cost
	// - Add a button (Bind OnClicked → call OnBuildingSelected(BuildingID))

	// ⚠️ This part is intentionally left for Blueprint customization 
	// or can be handled in C++ with UVerticalBox or similar if needed.
}
