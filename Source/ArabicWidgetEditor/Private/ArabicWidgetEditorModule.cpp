// Copyright 2026 Qn8r. Licensed under the Apache License, Version 2.0.

#include "ArabicWidgetTextComponent.h"
#include "ArabicWidgetTextComponentDetails.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

class FArabicWidgetEditorModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		FPropertyEditorModule& PropertyEditor =
			FModuleManager::LoadModuleChecked<FPropertyEditorModule>(
				TEXT("PropertyEditor")
			);

		PropertyEditor.RegisterCustomClassLayout(
			UArabicWidgetTextComponent::StaticClass()->GetFName(),
			FOnGetDetailCustomizationInstance::CreateStatic(
				&FArabicWidgetTextComponentDetails::MakeInstance
			)
		);

		PropertyEditor.NotifyCustomizationModuleChanged();
	}

	virtual void ShutdownModule() override
	{
		if (!FModuleManager::Get().IsModuleLoaded(TEXT("PropertyEditor")))
		{
			return;
		}

		FPropertyEditorModule& PropertyEditor =
			FModuleManager::GetModuleChecked<FPropertyEditorModule>(
				TEXT("PropertyEditor")
			);

		PropertyEditor.UnregisterCustomClassLayout(
			UArabicWidgetTextComponent::StaticClass()->GetFName()
		);

		PropertyEditor.NotifyCustomizationModuleChanged();
	}
};

IMPLEMENT_MODULE(FArabicWidgetEditorModule, ArabicWidgetEditor)
