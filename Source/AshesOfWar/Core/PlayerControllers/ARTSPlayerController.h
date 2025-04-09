#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ARTSPlayerController.generated.h"

class AUnit;

/**
 * ARTSPlayerController
 * Custom PlayerController handling unit selection and right-click orders for RTS gameplay.
 */
UCLASS()
class ASHESOFWAR_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Constructor
	ARTSPlayerController();

protected:
	// Sets up player input bindings
	virtual void SetupInputComponent() override;

	// Handles left-click input (selection)
	void HandleLeftClick();

	// Handles right-click input (orders)
	void HandleRightClick();

public:
	// Temporarily supports single unit selection
	void SetSelectedUnit(AUnit* NewUnit);

private:
	// Currently selected unit
	UPROPERTY()
	AUnit* SelectedUnit;
};
