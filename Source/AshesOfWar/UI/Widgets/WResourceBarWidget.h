#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WResourceBarWidget.generated.h"

// Forward declaration
class UTextBlock;

/**
 * UWResourceBarWidget
 * 
 * Widget responsible for displaying the player's current resource counts
 * (Aetherium, Vitae, Umbra) at the top of the RTS game screen.
 * 
 * This widget expects to be bound to three UMG TextBlocks named:
 * - Txt_Aetherium
 * - Txt_Vitae
 * - Txt_Umbra
 */
UCLASS()
class ASHESOFWAR_API UWResourceBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * Updates the resource values displayed in the UI.
	 * Typically called every second by the PlayerController via a timer.
	 * 
	 * @param Aetherium - The current Aetherium resource count.
	 * @param Vitae - The current Vitae resource count.
	 * @param Umbra - The current Umbra resource count.
	 */
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateResources(int32 Aetherium, int32 Vitae, int32 Umbra);

protected:
	/** Text block displaying the amount of Aetherium. Must be bound in the UMG widget. */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Txt_Aetherium;

	/** Text block displaying the amount of Vitae. Must be bound in the UMG widget. */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Txt_Vitae;

	/** Text block displaying the amount of Umbra. Must be bound in the UMG widget. */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Txt_Umbra;
};
