#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

// Forward declaration
class AUnit;

/**
 * AMainHUD
 * 
 * The class responsible for displaying the main RTS HUD.
 * Handles selection rectangle drawing and unit selection logic.
 */
UCLASS()
class ASHESOFWAR_API AMainHUD : public AHUD
{
	GENERATED_BODY()

private:
	/** Whether the selection rectangle is currently being drawn. */
	bool bDrawSelectionRect{false};

	/** Top-left corner position of the selection rectangle. */
	FVector2D SelectionRectStart;

	/** Size (width and height) of the selection rectangle. */
	FVector2D SelectionRectSize;

	/** Color of the selection rectangle (default is semi-transparent blue). */
	FLinearColor SelectionRectColor = FLinearColor(0.0f, 0.5f, 1.0f, 0.25f);

	/** List of units currently selected. */
	UPROPERTY()
	TArray<AUnit*> SelectedUnits;

protected:
	/** Called every frame to render HUD elements. */
	virtual void DrawHUD() override;

public:
	/**
	 * Starts showing the selection rectangle with specified parameters.
	 */
	void ShowSelectionRect(const FVector2D& Start, const FVector2D& Size, const FLinearColor& Color = FLinearColor(0.0f, 0.5f, 1.0f, 0.25f));

	/**
	 * Hides the selection rectangle and finalizes the unit selection.
	 */
	void HideSelectionRect();
};
