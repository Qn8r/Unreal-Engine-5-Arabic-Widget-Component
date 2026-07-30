// Copyright 2026 Qn8r. Licensed under the Apache License, Version 2.0.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class IDetailLayoutBuilder;
class IPropertyUtilities;
class SWidget;

enum class EArabicWidgetTextPanelLanguage : uint8;

/** لوحة Details للمكوّن. */
class ARABICWIDGETEDITOR_API FArabicWidgetTextComponentDetails final
	: public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(
		IDetailLayoutBuilder& DetailBuilder
	) override;

private:
	/** قائمة اللغة. */
	TSharedRef<SWidget> BuildLanguageMenu();

	/** اسم اللغة الحالية. */
	FText GetCurrentLanguageText() const;

	/** يحفظ اللغة. */
	void SetLanguage(
		EArabicWidgetTextPanelLanguage NewLanguage
	);

	TWeakPtr<IPropertyUtilities> PropertyUtilities;
};
