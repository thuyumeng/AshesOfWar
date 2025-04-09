#include "WResourceBarWidget.h"
#include "Components/TextBlock.h"

void UWResourceBarWidget::UpdateResources(int32 Aetherium, int32 Vitae, int32 Umbra)
{
	// Update the displayed value of Aetherium if the widget is bound
	if (Txt_Aetherium)
	{
		Txt_Aetherium->SetText(FText::AsNumber(Aetherium));
	}

	// Update the displayed value of Vitae
	if (Txt_Vitae)
	{
		Txt_Vitae->SetText(FText::AsNumber(Vitae));
	}

	// Update the displayed value of Umbra
	if (Txt_Umbra)
	{
		Txt_Umbra->SetText(FText::AsNumber(Umbra));
	}
}
