// Copyright 2026 Qn8r. Licensed under the Apache License, Version 2.0.

#include "ArabicWidgetTextComponentDetails.h"

#include "ArabicWidgetTextComponent.h"
#include "ArabicWidgetTextEditorSettings.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Framework/Commands/UIAction.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "IDetailPropertyRow.h"
#include "IPropertyUtilities.h"
#include "PropertyHandle.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Text/STextBlock.h"

namespace ArabicWidgetTextDetails
{
	EArabicWidgetTextPanelLanguage GetLanguage()
	{
		return GetDefault<UArabicWidgetTextEditorSettings>()
			->PanelLanguage;
	}

	FText Label(
		const TCHAR* English,
		const TCHAR* Arabic
	)
	{
		switch (GetLanguage())
		{
		case EArabicWidgetTextPanelLanguage::Arabic:
			return FText::FromString(Arabic);

		case EArabicWidgetTextPanelLanguage::Bilingual:
			return FText::FromString(
				FString::Printf(
					TEXT("%s | %s"),
					English,
					Arabic
				)
			);

		case EArabicWidgetTextPanelLanguage::English:
		default:
			return FText::FromString(English);
		}
	}

	void AddProperty(
		IDetailLayoutBuilder& DetailBuilder,
		IDetailCategoryBuilder& Category,
		const FName PropertyName,
		const TCHAR* English,
		const TCHAR* Arabic
	)
	{
		const TSharedRef<IPropertyHandle> Handle =
			DetailBuilder.GetProperty(
				PropertyName,
				UArabicWidgetTextComponent::StaticClass()
			);

		if (!Handle->IsValidHandle())
		{
			return;
		}

		DetailBuilder.HideProperty(Handle);

		Category
			.AddProperty(Handle)
			.DisplayName(Label(English, Arabic));
	}
}

TSharedRef<IDetailCustomization>
FArabicWidgetTextComponentDetails::MakeInstance()
{
	return MakeShared<
		FArabicWidgetTextComponentDetails
	>();
}

void FArabicWidgetTextComponentDetails::CustomizeDetails(
	IDetailLayoutBuilder& DetailBuilder
)
{
	using namespace ArabicWidgetTextDetails;

	PropertyUtilities =
		DetailBuilder.GetPropertyUtilities();

	DetailBuilder.HideCategory(
		TEXT("Arabic Widget Text")
	);

	DetailBuilder.HideCategory(
		TEXT("Arabic Widget Text|Content")
	);

	DetailBuilder.HideCategory(
		TEXT("Arabic Widget Text|Appearance")
	);

	DetailBuilder.HideCategory(
		TEXT("Arabic Widget Text|Background")
	);

	DetailBuilder.HideCategory(
		TEXT("Arabic Widget Text|Layout")
	);

	DetailBuilder.HideCategory(
		TEXT("Arabic Widget Text|Two Sided")
	);

	DetailBuilder.HideCategory(
		TEXT("Arabic Widget Text|Camera")
	);

	DetailBuilder.HideCategory(
		TEXT("Arabic Widget Text|Performance")
	);

	IDetailCategoryBuilder& PanelCategory =
		DetailBuilder.EditCategory(
			TEXT("ArabicWidgetText.Panel"),
			Label(
				TEXT("Arabic Widget Text"),
				TEXT("النص العربي")
			),
			ECategoryPriority::Important
		);

	PanelCategory
		.AddCustomRow(
			Label(
				TEXT("Panel Language"),
				TEXT("لغة اللوحة")
			)
		)
		.NameContent()
		[
			SNew(STextBlock)
				.Text(
					Label(
						TEXT("Panel Language"),
						TEXT("لغة اللوحة")
					)
				)
				.Font(
					IDetailLayoutBuilder::GetDetailFont()
				)
		]
	.ValueContent()
		.MinDesiredWidth(180.0f)
		[
			SNew(SComboButton)
				.OnGetMenuContent(
					this,
					&FArabicWidgetTextComponentDetails::
					BuildLanguageMenu
				)
				.ButtonContent()
				[
					SNew(STextBlock)
						.Text(
							this,
							&FArabicWidgetTextComponentDetails::
							GetCurrentLanguageText
						)
				]
		];

	IDetailCategoryBuilder& ContentCategory =
		DetailBuilder.EditCategory(
			TEXT("ArabicWidgetText.Content"),
			Label(
				TEXT("Content"),
				TEXT("المحتوى")
			),
			ECategoryPriority::Important
		);

	AddProperty(
		DetailBuilder,
		ContentCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			Text
		),
		TEXT("Text"),
		TEXT("النص")
	);

	IDetailCategoryBuilder& AppearanceCategory =
		DetailBuilder.EditCategory(
			TEXT("ArabicWidgetText.Appearance"),
			Label(
				TEXT("Appearance"),
				TEXT("المظهر")
			)
		);

	AddProperty(
		DetailBuilder,
		AppearanceCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			Font
		),
		TEXT("Font"),
		TEXT("الخط")
	);

	AddProperty(
		DetailBuilder,
		AppearanceCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			TextColor
		),
		TEXT("Color"),
		TEXT("اللون")
	);

	AddProperty(
		DetailBuilder,
		AppearanceCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			ShadowOffset
		),
		TEXT("Shadow Offset"),
		TEXT("إزاحة الظل")
	);

	AddProperty(
		DetailBuilder,
		AppearanceCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			ShadowColor
		),
		TEXT("Shadow Color"),
		TEXT("لون الظل")
	);

	IDetailCategoryBuilder& BackgroundCategory =
		DetailBuilder.EditCategory(
			TEXT("ArabicWidgetText.Background"),
			Label(
				TEXT("Background"),
				TEXT("الخلفية")
			)
		);

	AddProperty(
		DetailBuilder,
		BackgroundCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			PanelBackgroundColor
		),
		TEXT("Background Color"),
		TEXT("لون الخلفية")
	);

	AddProperty(
		DetailBuilder,
		BackgroundCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			BackgroundPadding
		),
		TEXT("Padding"),
		TEXT("الهوامش الداخلية")
	);

	IDetailCategoryBuilder& LayoutCategory =
		DetailBuilder.EditCategory(
			TEXT("ArabicWidgetText.Layout"),
			Label(
				TEXT("Layout"),
				TEXT("التخطيط")
			)
		);

	AddProperty(
		DetailBuilder,
		LayoutCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			bAutoWrapText
		),
		TEXT("Auto Wrap"),
		TEXT("التفاف النص تلقائيًا")
	);

	AddProperty(
		DetailBuilder,
		LayoutCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			MaximumTextWidth
		),
		TEXT("Maximum Width"),
		TEXT("أقصى عرض")
	);

	AddProperty(
		DetailBuilder,
		LayoutCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			HorizontalAlignment
		),
		TEXT("Alignment"),
		TEXT("المحاذاة")
	);

	AddProperty(
		DetailBuilder,
		LayoutCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			TextDirection
		),
		TEXT("Direction"),
		TEXT("اتجاه النص")
	);

	IDetailCategoryBuilder& TwoSidedCategory =
		DetailBuilder.EditCategory(
			TEXT("ArabicWidgetText.TwoSided"),
			Label(
				TEXT("Two Sided"),
				TEXT("العرض من الجهتين")
			)
		);

	AddProperty(
		DetailBuilder,
		TwoSidedCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			TwoSidedMode
		),
		TEXT("Mode"),
		TEXT("وضع العرض")
	);

	AddProperty(
		DetailBuilder,
		TwoSidedCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			bMatchFrontAppearance
		),
		TEXT("Use Front Colors"),
		TEXT("استخدام ألوان الجهة الأمامية")
	);

	AddProperty(
		DetailBuilder,
		TwoSidedCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			BackTextColor
		),
		TEXT("Back Text Color"),
		TEXT("لون النص في الجهة الخلفية")
	);

	AddProperty(
		DetailBuilder,
		TwoSidedCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			BackPanelBackgroundColor
		),
		TEXT("Back Background Color"),
		TEXT("لون خلفية الجهة الخلفية")
	);

	IDetailCategoryBuilder& CameraCategory =
		DetailBuilder.EditCategory(
			TEXT("ArabicWidgetText.Camera"),
			Label(
				TEXT("Camera"),
				TEXT("الكاميرا")
			)
		);

	AddProperty(
		DetailBuilder,
		CameraCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			FaceCameraMode
		),
		TEXT("Face Camera"),
		TEXT("مواجهة الكاميرا")
	);

	AddProperty(
		DetailBuilder,
		CameraCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			CameraPlayerIndex
		),
		TEXT("Player Index"),
		TEXT("رقم اللاعب")
	);

	AddProperty(
		DetailBuilder,
		CameraCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			FaceCameraRotationOffset
		),
		TEXT("Rotation Offset"),
		TEXT("إزاحة الدوران")
	);

	IDetailCategoryBuilder& PerformanceCategory =
		DetailBuilder.EditCategory(
			TEXT("ArabicWidgetText.Performance"),
			Label(
				TEXT("Performance"),
				TEXT("الأداء")
			)
		);

	AddProperty(
		DetailBuilder,
		PerformanceCategory,
		GET_MEMBER_NAME_CHECKED(
			UArabicWidgetTextComponent,
			MaxRenderDistance
		),
		TEXT("Max Render Distance"),
		TEXT("أقصى مسافة للعرض")
	);
}

TSharedRef<SWidget>
FArabicWidgetTextComponentDetails::BuildLanguageMenu()
{
	FMenuBuilder MenuBuilder(
		true,
		nullptr
	);

	MenuBuilder.AddMenuEntry(
		FText::FromString(TEXT("English")),
		FText::GetEmpty(),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateRaw(
				this,
				&FArabicWidgetTextComponentDetails::
				SetLanguage,
				EArabicWidgetTextPanelLanguage::English
			)
		)
	);

	MenuBuilder.AddMenuEntry(
		FText::FromString(TEXT("العربية")),
		FText::GetEmpty(),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateRaw(
				this,
				&FArabicWidgetTextComponentDetails::
				SetLanguage,
				EArabicWidgetTextPanelLanguage::Arabic
			)
		)
	);

	MenuBuilder.AddMenuEntry(
		FText::FromString(
			TEXT("English | العربية")
		),
		FText::GetEmpty(),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateRaw(
				this,
				&FArabicWidgetTextComponentDetails::
				SetLanguage,
				EArabicWidgetTextPanelLanguage::Bilingual
			)
		)
	);

	return MenuBuilder.MakeWidget();
}

FText
FArabicWidgetTextComponentDetails::GetCurrentLanguageText()
const
{
	switch (
		GetDefault<UArabicWidgetTextEditorSettings>()
		->PanelLanguage
		)
	{
	case EArabicWidgetTextPanelLanguage::Arabic:
		return FText::FromString(TEXT("العربية"));

	case EArabicWidgetTextPanelLanguage::Bilingual:
		return FText::FromString(
			TEXT("English | العربية")
		);

	case EArabicWidgetTextPanelLanguage::English:
	default:
		return FText::FromString(TEXT("English"));
	}
}

void FArabicWidgetTextComponentDetails::SetLanguage(
	const EArabicWidgetTextPanelLanguage NewLanguage
)
{
	UArabicWidgetTextEditorSettings* Settings =
		GetMutableDefault<
		UArabicWidgetTextEditorSettings
		>();

	if (Settings->PanelLanguage == NewLanguage)
	{
		return;
	}

	Settings->PanelLanguage = NewLanguage;
	Settings->SaveConfig();

	if (
		const TSharedPtr<IPropertyUtilities> Utilities =
		PropertyUtilities.Pin()
		)
	{
		Utilities->ForceRefresh();
	}
}
