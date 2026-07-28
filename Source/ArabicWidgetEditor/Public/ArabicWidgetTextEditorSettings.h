#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ArabicWidgetTextEditorSettings.generated.h"

/** لغة لوحة Details الخاصة بالمكوّن. */
UENUM()
enum class EArabicWidgetTextPanelLanguage : uint8
{
	English,
	Arabic,
	Bilingual
};

/** تفضيل محفوظ لكل مستخدم للغة لوحة Details. */
UCLASS(Config = EditorPerProjectUserSettings)
class ARABICWIDGETEDITOR_API UArabicWidgetTextEditorSettings : public UObject
{
	GENERATED_BODY()

public:
	/** العرض الثنائي هو الافتراضي لتسهيل التطوير والبحث. */
	UPROPERTY(Config)
	EArabicWidgetTextPanelLanguage PanelLanguage =
		EArabicWidgetTextPanelLanguage::Bilingual;
};
