#include "WResourceBarWidget.h"
#include "Components/TextBlock.h"

void UWResourceBarWidget::UpdateResources(int32 Aetherium, int32 Vitae, int32 Umbra)
{
	if (Txt_Aetherium)
		Txt_Aetherium->SetText(FText::AsNumber(Aetherium));
	if (Txt_Vitae)
		Txt_Vitae->SetText(FText::AsNumber(Vitae));
	if (Txt_Umbra)
		Txt_Umbra->SetText(FText::AsNumber(Umbra));
}
