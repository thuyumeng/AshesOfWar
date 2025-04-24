#pragma once

// --- Includes ---
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ARTSPlayerController.generated.h"

// --- Forward Declarations ---
class AUnit;
class UWResourceBarWidget;
class AMainHUD;

/**
 * ARTSPlayerController
 * 
 * Custom RTS-style PlayerController:
 * - Handles selection, input and HUD updates
 * - Manages the top-bar resource UI
 */
UCLASS()
class ASHESOFWAR_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// --- Constructor ---
	ARTSPlayerController();

protected:
	// --- Lifecycle Hooks ---
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;

	// --- Input Handling ---
	void HandleLeftClick();
	void HandleLeftClickRelease();
	void HandleRightClick();

	// --- HUD Update ---
	void UpdateResourceUI();

public:
	/** Sets the list of currently selected units */
	void SetSelectedUnits(TArray<AUnit*>& NewUnits);

private:
	// --- Selection ---
	UPROPERTY()
	TArray<TObjectPtr<AUnit>> SelectedUnits;

	UPROPERTY()
	bool bIsMousePressed{false};

	FVector2D SelectionStartPosition;

	// --- HUD / UI ---
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UWResourceBarWidget> ResourceBarClass;

	UPROPERTY()
	UWResourceBarWidget* ResourceBarInstance;

	UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AMainHUD> MainHUD;

	FTimerHandle ResourceUpdateTimerHandle;
};
