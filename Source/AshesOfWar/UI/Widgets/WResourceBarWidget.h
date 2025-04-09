
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WResourceBarWidget.generated.h"

class UTextBlock;

UCLASS()
class ASHESOFWAR_API UWResourceBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Met à jour les valeurs affichées dans l’UI
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateResources(int32 Aetherium, int32 Vitae, int32 Umbra);

protected:
	// Ces widgets doivent exister dans le Blueprint et porter exactement ces noms
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Txt_Aetherium;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Txt_Vitae;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Txt_Umbra;
};
