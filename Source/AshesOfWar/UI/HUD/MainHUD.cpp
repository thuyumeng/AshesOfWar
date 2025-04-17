#include "MainHUD.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "AshesOfWar/Core/PlayerControllers/ARTSPlayerController.h"

void AMainHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw the selection rectangle if active
	if (bDrawSelectionRect)
	{
		DrawRect(
			SelectionRectColor,
			SelectionRectStart.X,
			SelectionRectStart.Y,
			SelectionRectSize.X,
			SelectionRectSize.Y);

		// Update the list of units currently within the selection box
		GetActorsInSelectionRectangle<AUnit>(
			SelectionRectStart,
			SelectionRectStart + SelectionRectSize,
			SelectedUnits,
			false
		);
	}
}

void AMainHUD::ShowSelectionRect(const FVector2D& Start, const FVector2D& Size, const FLinearColor& Color)
{
	bDrawSelectionRect = true;
	SelectionRectStart = Start;
	SelectionRectSize = Size;
	SelectionRectColor = Color;
}

void AMainHUD::HideSelectionRect()
{
	if (!bDrawSelectionRect)
	{
		return;
	}

	bDrawSelectionRect = false;

	// Notify the player controller of the selected units
	if (ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(GetOwningPlayerController()))
	{
		PlayerController->SetSelectedUnits(SelectedUnits);
	}

	// Clear the list for the next selection
	SelectedUnits.Empty();
}
