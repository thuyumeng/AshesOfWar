#include "WResourceBarWidget.h"
#include "Components/TextBlock.h"

void UWResourceBarWidget::UpdateResources(int32 Aetherium, int32 Vitae, int32 Umbra)
{
	// Update Aetherium display if the TextBlock is valid
	if (Txt_Aetherium)
	{
		Txt_Aetherium->SetText(FText::AsNumber(Aetherium));
	}

	// Update Vitae display
	if (Txt_Vitae)
	{
		Txt_Vitae->SetText(FText::AsNumber(Vitae));
	}

	// Update Umbra display
	if (Txt_Umbra)
	{
		Txt_Umbra->SetText(FText::AsNumber(Umbra));
	}
}
