#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ARTSPlayerController.generated.h"

class AUnit;
class UWResourceBarWidget;

/**
 * ARTSPlayerController
 * Custom PlayerController handling unit selection and right-click orders for RTS gameplay.
 */
UCLASS()
class ASHESOFWAR_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARTSPlayerController();

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void HandleLeftClick();
	void HandleRightClick();

	// Met à jour l'affichage des ressources dans l'UI
	void UpdateResourceUI();

public:
	void SetSelectedUnit(AUnit* NewUnit);

private:
	UPROPERTY()
	AUnit* SelectedUnit;

	// --- UI Resource Bar --- //
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UWResourceBarWidget> ResourceBarClass;

	UPROPERTY()
	UWResourceBarWidget* ResourceBarInstance;

	FTimerHandle ResourceUpdateTimerHandle;
};
