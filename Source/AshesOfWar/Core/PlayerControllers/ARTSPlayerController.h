#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ARTSPlayerController.generated.h"

class AUnit;
class UWResourceBarWidget;
class AMainHUD;

/**
 * ARTSPlayerController
 * Custom PlayerController for RTS gameplay.
 * Handles unit selection and basic click-based interactions.
 * Also manages displaying and updating the top-screen resource UI.
 */
UCLASS()
class ASHESOFWAR_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Constructor
	ARTSPlayerController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void HandleLeftClickRelease();
	// Binds mouse click inputs
	virtual void SetupInputComponent() override;

	// Handles left click (unit selection)
	void HandleLeftClick();

	// Handles right click (issue move or interact order)
	void HandleRightClick();

	// Updates the resource UI (Aetherium, Vitae, Umbra)
	void UpdateResourceUI();

	virtual void Tick(float DeltaSeconds) override;

public:
	// Set the currently selected unit
	void SetSelectedUnit(AUnit* NewUnit);
	void SetMultipleSelectedUnits(TArray<AUnit*>& NewUnits);

private:
	// The currently selected unit (if any)
	UPROPERTY()
	TObjectPtr<AUnit> SelectedUnit;

	// The currently multiple selected units (if any)
	UPROPERTY()
	TArray<TObjectPtr<AUnit>> SelectedUnits;

	// The multiple selection box property
	UPROPERTY()
	bool bIsMousePressed{false};

	// --- UI: Resource Bar --- //

	// Widget class reference to instantiate the resource bar
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UWResourceBarWidget> ResourceBarClass;

	// Widget that used for display the rect area of marquee selection
	UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AMainHUD> MainHUD;
	FVector2D SelectionStartPosition;
	
	
	// Widget instance shown in-game
	UPROPERTY()
	UWResourceBarWidget* ResourceBarInstance;

	// Timer to update the resource UI regularly
	FTimerHandle ResourceUpdateTimerHandle;
};
