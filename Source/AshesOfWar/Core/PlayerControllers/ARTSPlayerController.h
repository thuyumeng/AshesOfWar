#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ARTSPlayerController.generated.h"

class AUnit;
class UWResourceBarWidget;

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

	// Binds mouse click inputs
	virtual void SetupInputComponent() override;

	// Handles left click (unit selection)
	void HandleLeftClick();

	// Handles right click (issue move or interact order)
	void HandleRightClick();

	// Updates the resource UI (Aetherium, Vitae, Umbra)
	void UpdateResourceUI();

public:
	// Set the currently selected unit
	void SetSelectedUnit(AUnit* NewUnit);

private:
	// The currently selected unit (if any)
	UPROPERTY()
	AUnit* SelectedUnit;

	// --- UI: Resource Bar --- //

	// Widget class reference to instantiate the resource bar
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UWResourceBarWidget> ResourceBarClass;

	// Widget instance shown in-game
	UPROPERTY()
	UWResourceBarWidget* ResourceBarInstance;

	// Timer to update the resource UI regularly
	FTimerHandle ResourceUpdateTimerHandle;
};
