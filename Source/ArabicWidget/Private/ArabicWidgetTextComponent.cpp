// Copyright 2026 Qn8r. Licensed under the Apache License, Version 2.0.

#include "ArabicWidgetTextComponent.h"

#include "Camera/PlayerCameraManager.h"
#include "Engine/Font.h"
#include "Engine/World.h"
#include "Framework/Text/TextLayout.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Math/TransformCalculus2D.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateColor.h"
#include "UObject/ConstructorHelpers.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "ArabicWidgetTextComponent"

namespace ArabicWidgetText
{
	ETextJustify::Type ToJustification(
		const EArabicWidgetTextAlignment Alignment
	)
	{
		switch (Alignment)
		{
		case EArabicWidgetTextAlignment::Left:
			return ETextJustify::Left;

		case EArabicWidgetTextAlignment::Right:
			return ETextJustify::Right;

		case EArabicWidgetTextAlignment::Center:
		default:
			return ETextJustify::Center;
		}
	}

	ETextFlowDirection ToFlowDirection(
		const EArabicWidgetTextDirection Direction
	)
	{
		switch (Direction)
		{
		case EArabicWidgetTextDirection::LeftToRight:
			return ETextFlowDirection::LeftToRight;

		case EArabicWidgetTextDirection::RightToLeft:
			return ETextFlowDirection::RightToLeft;

		case EArabicWidgetTextDirection::Culture:
			return ETextFlowDirection::Culture;

		case EArabicWidgetTextDirection::Auto:
		default:
			return ETextFlowDirection::Auto;
		}
	}

	// خط المحرك عند عدم وجود خط.
	FSlateFontInfo ResolveFont(const FSlateFontInfo& Source)
	{
		if (Source.HasValidFont())
		{
			return Source;
		}

		FSlateFontInfo Result =
			FCoreStyle::GetDefaultFontStyle(
				TEXT("Regular"),
				FMath::Max(1, Source.Size)
			);

		Result.LetterSpacing = Source.LetterSpacing;
		Result.SkewAmount = Source.SkewAmount;
		Result.OutlineSettings = Source.OutlineSettings;
		Result.FontMaterial = Source.FontMaterial;
		Result.bForceMonospaced = Source.bForceMonospaced;
		Result.MonospacedWidth = Source.MonospacedWidth;

		return Result;
	}

	TSharedRef<SBorder> CreateSurface(
		const FText& Text,
		const FSlateFontInfo& Font,
		const FLinearColor& TextColor,
		const FLinearColor& BackgroundColor,
		const FMargin& Padding,
		const FVector2D& ShadowOffset,
		const FLinearColor& ShadowColor,
		const EArabicWidgetTextAlignment Alignment,
		const EArabicWidgetTextDirection Direction,
		const bool bAutoWrap,
		const float MaximumWidth,
		const bool bMirrorHorizontally
	)
	{
		const float HorizontalScale =
			bMirrorHorizontally ? -1.0f : 1.0f;

		const float WrapWidth =
			bAutoWrap
			? FMath::Max(1.0f, MaximumWidth)
			: 0.0f;

		return SNew(SBorder)
			.BorderImage(
				FCoreStyle::Get().GetBrush(
					TEXT("WhiteBrush")
				)
			)
			.BorderBackgroundColor(
				FSlateColor(BackgroundColor)
			)
			.Padding(Padding)
			.RenderTransformPivot(
				FVector2D(0.5f, 0.5f)
			)
			.RenderTransform(
				FSlateRenderTransform(
					FScale2D(
						HorizontalScale,
						1.0f
					)
				)
			)
			[
				SNew(STextBlock)
					.Text(Text)
					.Font(ResolveFont(Font))
					.ColorAndOpacity(
						FSlateColor(TextColor)
					)
					.Justification(
						ToJustification(Alignment)
					)
					.TextFlowDirection(
						ToFlowDirection(Direction)
					)
					.TextShapingMethod(
						ETextShapingMethod::FullShaping
					)
					.AutoWrapText(bAutoWrap)
					.WrapTextAt(WrapWidth)
					.ShadowOffset(ShadowOffset)
					.ShadowColorAndOpacity(ShadowColor)
			];
	}
}

UArabicWidgetTextComponent::UArabicWidgetTextComponent()
{
	Text = LOCTEXT(
		"DefaultWidgetText",
		"نص عربي"
	);

	static ConstructorHelpers::FObjectFinder<UFont> DefaultArabicFont(
		TEXT("/ArabicWidget/Fonts/Amiri/F_Amiri.F_Amiri")
	);

	Font =
		DefaultArabicFont.Succeeded()
		? FSlateFontInfo(DefaultArabicFont.Object, 48)
		: FCoreStyle::GetDefaultFontStyle(TEXT("Regular"), 48);

	TextColor = FLinearColor::White;
	ShadowOffset = FVector2D::ZeroVector;
	ShadowColor = FLinearColor(
		0.0f,
		0.0f,
		0.0f,
		0.75f
	);

	PanelBackgroundColor =
		FLinearColor::Transparent;

	BackgroundPadding = FMargin(12.0f);

	bAutoWrapText = false;
	MaximumTextWidth = 600.0f;

	HorizontalAlignment =
		EArabicWidgetTextAlignment::Center;

	TextDirection =
		EArabicWidgetTextDirection::Auto;

	TwoSidedMode =
		EArabicWidgetTextTwoSidedMode::Off;

	bMatchFrontAppearance = true;
	BackTextColor = FLinearColor::White;
	BackPanelBackgroundColor =
		FLinearColor::Transparent;

	FaceCameraMode =
		EArabicWidgetTextFaceCameraMode::Off;

	CameraPlayerIndex = 0;
	FaceCameraRotationOffset =
		FRotator::ZeroRotator;

	MaxRenderDistance = 0.0f;

	BackWidgetComponent = nullptr;

	AppliedFaceCameraMode =
		EArabicWidgetTextFaceCameraMode::Off;

	SavedRelativeRotation =
		FRotator::ZeroRotator;

	bHasSavedRelativeRotation = false;

	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;

	SetWidgetSpace(EWidgetSpace::World);
	SetDrawAtDesiredSize(true);
	SetPivot(FVector2D(0.5f, 0.5f));
	SetBlendMode(EWidgetBlendMode::Transparent);
	SetTwoSided(false);

	SetEditTimeUsable(true);
	SetManuallyRedraw(false);
	SetRedrawTime(0.0f);
	SetTickMode(ETickMode::Automatic);
	SetTickWhenOffscreen(false);
	SetWindowFocusable(false);

	SetCastShadow(false);
	SetCanEverAffectNavigation(false);

	SetCollisionEnabled(
		ECollisionEnabled::NoCollision
	);

	SetGenerateOverlapEvents(false);
}

void UArabicWidgetTextComponent::OnRegister()
{
	Super::OnRegister();
	RefreshComponent();
}

void UArabicWidgetTextComponent::OnUnregister()
{
	SetSlateWidget(TSharedPtr<SWidget>());
	DestroyBackSurface();

	Super::OnUnregister();
}

void UArabicWidgetTextComponent::TickComponent(
	const float DeltaTime,
	const ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
)
{
	Super::TickComponent(
		DeltaTime,
		TickType,
		ThisTickFunction
	);

	UpdateFaceCamera();
}

void UArabicWidgetTextComponent::SetWorldText(
	const FText& NewText
)
{
	Text = NewText;
	RefreshComponent();
}

void UArabicWidgetTextComponent::SetFaceCameraMode(
	const EArabicWidgetTextFaceCameraMode NewMode
)
{
	FaceCameraMode = NewMode;

	SyncFaceCameraMode();
	SyncPerformanceSettings();
	UpdateFaceCamera();
}

void UArabicWidgetTextComponent::SetTwoSidedMode(
	const EArabicWidgetTextTwoSidedMode NewMode
)
{
	TwoSidedMode = NewMode;
	RefreshComponent();
}

void UArabicWidgetTextComponent::RefreshWorldText()
{
	RefreshComponent();
}

void UArabicWidgetTextComponent::SetMaterial(
	const int32 ElementIndex,
	UMaterialInterface* Material
)
{
	Super::SetMaterial(ElementIndex, Material);

	if (ElementIndex == 0)
	{
		SyncBackMaterial();
	}
}

void UArabicWidgetTextComponent::RefreshComponent()
{
	if (!IsRegistered())
	{
		return;
	}

	SyncFaceCameraMode();
	UpdateBackSurface();
	SyncPerformanceSettings();

	RebuildSurface(
		this,
		TextColor,
		PanelBackgroundColor,
		false
	);

	if (IsValid(BackWidgetComponent))
	{
		const FLinearColor EffectiveTextColor =
			bMatchFrontAppearance
			? TextColor
			: BackTextColor;

		const FLinearColor EffectiveBackgroundColor =
			bMatchFrontAppearance
			? PanelBackgroundColor
			: BackPanelBackgroundColor;

		const bool bMirrorBack =
			TwoSidedMode ==
			EArabicWidgetTextTwoSidedMode::MirroredBack;

		RebuildSurface(
			BackWidgetComponent,
			EffectiveTextColor,
			EffectiveBackgroundColor,
			bMirrorBack
		);
	}

	UpdateFaceCamera();

	RequestSurfaceUpdate(this);
	RequestSurfaceUpdate(BackWidgetComponent);
}

void UArabicWidgetTextComponent::RebuildSurface(
	UWidgetComponent* Surface,
	const FLinearColor& SurfaceTextColor,
	const FLinearColor& SurfaceBackgroundColor,
	const bool bMirrorHorizontally
)
{
	if (
		!IsValid(Surface) ||
		!Surface->IsRegistered()
		)
	{
		return;
	}

	Surface->SetSlateWidget(
		ArabicWidgetText::CreateSurface(
			Text,
			Font,
			SurfaceTextColor,
			SurfaceBackgroundColor,
			BackgroundPadding,
			ShadowOffset,
			ShadowColor,
			HorizontalAlignment,
			TextDirection,
			bAutoWrapText,
			MaximumTextWidth,
			bMirrorHorizontally
		)
	);
}

void UArabicWidgetTextComponent::UpdateBackSurface()
{
	// سطح منفصل للوجه الخلفي.
	SetTwoSided(false);

	if (
		TwoSidedMode ==
		EArabicWidgetTextTwoSidedMode::Off
		)
	{
		DestroyBackSurface();
		return;
	}

	if (!IsValid(BackWidgetComponent))
	{
		CreateBackSurface();
	}
	else
	{
		SyncBackSurface();
	}
}

void UArabicWidgetTextComponent::CreateBackSurface()
{
	AActor* OwnerActor = GetOwner();
	UWorld* World = GetWorld();

	if (
		!IsValid(OwnerActor) ||
		!IsValid(World)
		)
	{
		return;
	}

	const FName ComponentName =
		MakeUniqueObjectName(
			OwnerActor,
			UWidgetComponent::StaticClass(),
			TEXT("ArabicWidgetTextBack")
		);

	BackWidgetComponent =
		NewObject<UWidgetComponent>(
			OwnerActor,
			ComponentName,
			RF_Transient |
			RF_DuplicateTransient |
			RF_TextExportTransient
		);

	if (!IsValid(BackWidgetComponent))
	{
		return;
	}

	BackWidgetComponent->PrimaryComponentTick
		.bStartWithTickEnabled = true;

	BackWidgetComponent->SetTickMode(
		ETickMode::Automatic
	);

	BackWidgetComponent->SetMobility(
		GetMobility()
	);

	BackWidgetComponent->SetupAttachment(this);

	// يمنع تداخل السطحين.
	BackWidgetComponent->SetRelativeTransform(
		FTransform(
			FRotator(0.0f, 180.0f, 0.0f),
			FVector(-0.5f, 0.0f, 0.0f),
			FVector::OneVector
		)
	);

	BackWidgetComponent->RegisterComponentWithWorld(
		World
	);

	SyncBackSurface();
}

void UArabicWidgetTextComponent::SyncBackSurface()
{
	if (!IsValid(BackWidgetComponent))
	{
		return;
	}

	BackWidgetComponent->SetMobility(
		GetMobility()
	);

	BackWidgetComponent->SetWidgetSpace(
		EWidgetSpace::World
	);

	BackWidgetComponent->SetDrawAtDesiredSize(
		GetDrawAtDesiredSize()
	);

	BackWidgetComponent->SetDrawSize(
		GetDrawSize()
	);

	BackWidgetComponent->SetPivot(
		GetPivot()
	);

	BackWidgetComponent->SetBlendMode(
		GetBlendMode()
	);

	BackWidgetComponent->SetGeometryMode(
		GetGeometryMode()
	);

	BackWidgetComponent->SetCylinderArcAngle(
		GetCylinderArcAngle()
	);

	BackWidgetComponent->SetOwnerPlayer(
		GetOwnerPlayer()
	);

	BackWidgetComponent->SetEditTimeUsable(true);
	BackWidgetComponent->SetManuallyRedraw(false);
	BackWidgetComponent->SetRedrawTime(0.0f);
	BackWidgetComponent->SetTickMode(
		ETickMode::Automatic
	);
	BackWidgetComponent->SetTickWhenOffscreen(false);
	BackWidgetComponent->SetComponentTickEnabled(true);

	BackWidgetComponent->SetTwoSided(false);
	BackWidgetComponent->SetWindowFocusable(false);
	BackWidgetComponent->SetCastShadow(false);

	BackWidgetComponent->SetTintColorAndOpacity(
		FLinearColor::White
	);

	BackWidgetComponent->SetBackgroundColor(
		FLinearColor::Transparent
	);

	BackWidgetComponent->SetOpacityFromTexture(1.0f);

	BackWidgetComponent->SetCollisionEnabled(
		ECollisionEnabled::NoCollision
	);

	BackWidgetComponent->SetGenerateOverlapEvents(false);

	BackWidgetComponent->SetVisibility(
		GetVisibleFlag(),
		false
	);

	BackWidgetComponent->SetHiddenInGame(
		bHiddenInGame,
		false
	);

	BackWidgetComponent->SetTranslucentSortPriority(
		TranslucencySortPriority
	);

	BackWidgetComponent->SetCullDistance(
		FMath::Max(0.0f, MaxRenderDistance)
	);

	SyncBackMaterial();
}

void UArabicWidgetTextComponent::SyncBackMaterial()
{
	if (!IsValid(BackWidgetComponent))
	{
		return;
	}

	BackWidgetComponent->SetMaterial(
		0,
		GetMaterial(0)
	);
}

void UArabicWidgetTextComponent::DestroyBackSurface()
{
	if (!IsValid(BackWidgetComponent))
	{
		BackWidgetComponent = nullptr;
		return;
	}

	BackWidgetComponent->SetSlateWidget(
		TSharedPtr<SWidget>()
	);

	BackWidgetComponent->DestroyComponent();
	BackWidgetComponent = nullptr;
}

void UArabicWidgetTextComponent::SyncPerformanceSettings()
{
	const float CullDistance =
		FMath::Max(0.0f, MaxRenderDistance);

	SetManuallyRedraw(false);
	SetRedrawTime(0.0f);
	SetTickMode(ETickMode::Automatic);
	SetTickWhenOffscreen(false);
	SetCullDistance(CullDistance);
	SetComponentTickEnabled(true);

	if (!IsValid(BackWidgetComponent))
	{
		return;
	}

	BackWidgetComponent->SetManuallyRedraw(false);
	BackWidgetComponent->SetRedrawTime(0.0f);
	BackWidgetComponent->SetTickMode(
		ETickMode::Automatic
	);
	BackWidgetComponent->SetTickWhenOffscreen(false);
	BackWidgetComponent->SetComponentTickEnabled(true);
	BackWidgetComponent->SetCullDistance(CullDistance);
}

void UArabicWidgetTextComponent::RequestSurfaceUpdate(
	UWidgetComponent* Surface
)
{
	if (
		!IsValid(Surface) ||
		!Surface->IsRegistered()
		)
	{
		return;
	}

	Surface->RequestRenderUpdate();
	Surface->MarkRenderStateDirty();
}

void UArabicWidgetTextComponent::SyncFaceCameraMode()
{
	if (FaceCameraMode == AppliedFaceCameraMode)
	{
		return;
	}

	const bool bWasFacingCamera =
		AppliedFaceCameraMode !=
		EArabicWidgetTextFaceCameraMode::Off;

	const bool bWillFaceCamera =
		FaceCameraMode !=
		EArabicWidgetTextFaceCameraMode::Off;

	if (!bWasFacingCamera && bWillFaceCamera)
	{
		SavedRelativeRotation =
			GetRelativeRotation();

		bHasSavedRelativeRotation = true;
	}
	else if (
		bWasFacingCamera &&
		!bWillFaceCamera &&
		bHasSavedRelativeRotation
		)
	{
		SetRelativeRotation(
			SavedRelativeRotation
		);

		bHasSavedRelativeRotation = false;
	}

	AppliedFaceCameraMode = FaceCameraMode;
}

void UArabicWidgetTextComponent::UpdateFaceCamera()
{
	if (
		FaceCameraMode ==
		EArabicWidgetTextFaceCameraMode::Off
		)
	{
		return;
	}

	APlayerCameraManager* CameraManager =
		UGameplayStatics::GetPlayerCameraManager(
			this,
			CameraPlayerIndex
		);

	if (!IsValid(CameraManager))
	{
		return;
	}

	FVector DirectionToCamera =
		CameraManager->GetCameraLocation() -
		GetComponentLocation();

	if (
		FaceCameraMode ==
		EArabicWidgetTextFaceCameraMode::YawOnly
		)
	{
		DirectionToCamera.Z = 0.0f;
	}

	if (DirectionToCamera.IsNearlyZero())
	{
		return;
	}

	FRotator NewRotation =
		DirectionToCamera.Rotation();

	NewRotation.Roll = 0.0f;

	if (
		FaceCameraMode ==
		EArabicWidgetTextFaceCameraMode::YawOnly
		)
	{
		NewRotation.Pitch = 0.0f;
	}

	NewRotation += FaceCameraRotationOffset;

	SetWorldRotation(NewRotation);
}

#if WITH_EDITOR

void UArabicWidgetTextComponent::PostEditChangeProperty(
	FPropertyChangedEvent& PropertyChangedEvent
)
{
	Super::PostEditChangeProperty(
		PropertyChangedEvent
	);

	RefreshComponent();
}

void UArabicWidgetTextComponent::PostEditUndo()
{
	Super::PostEditUndo();
	RefreshComponent();
}

#endif

#undef LOCTEXT_NAMESPACE
