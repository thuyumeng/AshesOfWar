#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WResourceBarWidget.generated.h"

class UTextBlock;

/**
 * UWResourceBarWidget
 * 
 * Widget class responsible for displaying the player's current resources (Aetherium, Vitae, Umbra)
 * on the top of the screen during RTS gameplay. It is bound to a UMG Widget Blueprint containing
 * three UTextBlocks named: Txt_Aetherium, Txt_Vitae, and Txt_Umbra.
 */
UCLASS()
class ASHESOFWAR_API UWResourceBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * Update the resource values displayed in the UI.
	 * This method is called by the PlayerController every second via timer.
	 * @param Aetherium The current amount of Aetherium the player owns
	 * @param Vitae The current amount of Vitae the player owns
	 * @param Umbra The current amount of Umbra the player owns
	 */
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateResources(int32 Aetherium, int32 Vitae, int32 Umbra);

protected:
	/** Text block displaying the Aetherium amount. Must be named Txt_Aetherium in the Blueprint. */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Txt_Aetherium;

	/** Text block displaying the Vitae amount. Must be named Txt_Vitae in the Blueprint. */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Txt_Vitae;

	/** Text block displaying the Umbra amount. Must be named Txt_Umbra in the Blueprint. */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Txt_Umbra;
};
