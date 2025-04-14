// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"

#include "Chaos/ChaosPerfTest.h"

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
	}
}
