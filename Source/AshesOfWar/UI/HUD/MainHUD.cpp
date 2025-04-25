// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "AshesOfWar/Core/PlayerControllers/ARTSPlayerController.h"
#include "Kismet/GameplayStatics.h"

AMainHUD::AMainHUD(): SelectionRectStart(), SelectionRectSize()
{
	// load the right click decal material
	if (RightClickDecalMaterialInterface.IsNull())
	{
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> DecalMaterial(
			TEXT("/Game/Material/MouseEffect/M_RightClickEffect.M_RightClickEffect"));
		if (DecalMaterial.Succeeded())
		{
			RightClickDecalMaterialInterface = DecalMaterial.Object;
		}
	}
}

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
		return;
	bDrawSelectionRect = false;
	if (ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(GetOwningPlayerController()))
	{
		PlayerController->SetSelectedUnits(SelectedUnits);
	}
	// clear the SelectedUnits
	SelectedUnits.Empty();
}

void AMainHUD::ShowRightClickEffect(const FVector& TargetLocation) const
{
	UGameplayStatics::SpawnDecalAtLocation(
		GetWorld(),
		RightClickDecalMaterialInterface.Get(),
		FVector(100.f, 100.f, 100.f),
		TargetLocation,
		FRotator(90.f, 0.f, 0.f),
		2.0f   // life in seconds
	);
}
