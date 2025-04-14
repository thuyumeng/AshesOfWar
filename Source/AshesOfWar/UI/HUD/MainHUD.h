// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/**
 *  the class that will be used to display the main HUD
 */
class AUnit;
UCLASS()
class ASHESOFWAR_API AMainHUD : public AHUD
{
	GENERATED_BODY()
private:
	bool bDrawSelectionRect{false};
	FVector2D SelectionRectStart;
	FVector2D SelectionRectSize;
	FLinearColor SelectionRectColor = FLinearColor(0.0f, 0.5f, 1.0f, 0.25f);

	UPROPERTY()
	TArray<AUnit*> SelectedUnits;

protected:
	virtual void DrawHUD() override;
public:
	void ShowSelectionRect(const FVector2D& Start, const FVector2D& Size, const FLinearColor& Color= FLinearColor(0.0f, 0.5f, 1.0f, 0.25f));
	void HideSelectionRect();
};
