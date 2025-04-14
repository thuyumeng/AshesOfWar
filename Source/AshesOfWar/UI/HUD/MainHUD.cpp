// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "AshesOfWar/Core/PlayerControllers/ARTSPlayerController.h"

void AMainHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw the selection rectangle if it is valid
	if (bDrawSelectionRect)
	{
		DrawRect(
			SelectionRectColor,
			SelectionRectStart.X,
			SelectionRectStart.Y,
			SelectionRectSize.X,
			SelectionRectSize.Y);

		// This function can only be called when dragging the selection box
		GetActorsInSelectionRectangle<AUnit>(SelectionRectStart, SelectionRectStart + SelectionRectSize, SelectedUnits, false);
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
		return;
	bDrawSelectionRect = false;
	ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(GetOwningPlayerController());
	if (PlayerController)
	{
		PlayerController->SetMultipleSelectedUnits(SelectedUnits);
	}
}