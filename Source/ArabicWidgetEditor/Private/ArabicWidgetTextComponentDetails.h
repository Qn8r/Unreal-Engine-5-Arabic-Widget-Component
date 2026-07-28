#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class IDetailLayoutBuilder;
class IPropertyUtilities;
class SWidget;

enum class EArabicWidgetTextPanelLanguage : uint8;

/** تخصيص مترجم للوحة Details الخاصة بالمكوّن. */
class ARABICWIDGETEDITOR_API FArabicWidgetTextComponentDetails final
	: public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(
		IDetailLayoutBuilder& DetailBuilder
	) override;

private:
	/** يبني قائمة اللغة: العربية أو الإنجليزية أو كلتاهما. */
	TSharedRef<SWidget> BuildLanguageMenu();

	/** يعيد اسم لغة اللوحة المحددة حالياً. */
	FText GetCurrentLanguageText() const;

	/** يحفظ التفضيل ويحدّث لوحة Details. */
	void SetLanguage(
		EArabicWidgetTextPanelLanguage NewLanguage
	);

	TWeakPtr<IPropertyUtilities> PropertyUtilities;
};
