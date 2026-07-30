// Copyright 2026 Qn8r. Licensed under the Apache License, Version 2.0.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ArabicWidgetTextEditorSettings.generated.h"

/** لغة لوحة Details. */
UENUM()
enum class EArabicWidgetTextPanelLanguage : uint8
{
	English,
	Arabic,
	Bilingual
};

/** إعداد لغة اللوحة. */
UCLASS(Config = EditorPerProjectUserSettings)
class ARABICWIDGETEDITOR_API UArabicWidgetTextEditorSettings : public UObject
{
	GENERATED_BODY()

public:
	/** الوضع الافتراضي ثنائي. */
	UPROPERTY(Config)
	EArabicWidgetTextPanelLanguage PanelLanguage =
		EArabicWidgetTextPanelLanguage::Bilingual;
};
