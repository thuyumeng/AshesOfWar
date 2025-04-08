#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ARTSPlayerController.generated.h"

class AUnit;

UCLASS()
class ASHESOFWAR_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARTSPlayerController();

protected:
	virtual void SetupInputComponent() override;

	// Gestion des clics
	void HandleLeftClick();
	void HandleRightClick();

public:
	// Temporairement, sélection d'une seule unité
	void SetSelectedUnit(AUnit* NewUnit);

private:
	UPROPERTY()
	AUnit* SelectedUnit;
};
