// Copyright 2026 Qn8r. Licensed under the Apache License, Version 2.0.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Fonts/SlateFontInfo.h"
#include "ArabicWidgetTextComponent.generated.h"

class UMaterialInterface;

/** محاذاة النص. */
UENUM(BlueprintType)
enum class EArabicWidgetTextAlignment : uint8
{
	Left	UMETA(DisplayName = "Left"),
	Center	UMETA(DisplayName = "Center"),
	Right	UMETA(DisplayName = "Right")
};

/** اتجاه النص. */
UENUM(BlueprintType)
enum class EArabicWidgetTextDirection : uint8
{
	Auto			UMETA(DisplayName = "Automatic"),
	LeftToRight		UMETA(DisplayName = "Left to Right"),
	RightToLeft		UMETA(DisplayName = "Right to Left"),
	Culture			UMETA(DisplayName = "Current Game Language")
};

/** مواجهة الكاميرا. */
UENUM(BlueprintType)
enum class EArabicWidgetTextFaceCameraMode : uint8
{
	Off			UMETA(DisplayName = "Off"),
	YawOnly		UMETA(DisplayName = "Yaw Only"),
	Full		UMETA(DisplayName = "Full")
};

/** عرض الوجه الخلفي. */
UENUM(BlueprintType)
enum class EArabicWidgetTextTwoSidedMode : uint8
{
	Off				UMETA(DisplayName = "Off"),
	MirroredBack	UMETA(DisplayName = "Mirrored Back"),
	ReadableBack	UMETA(DisplayName = "Readable Back")
};

/** نص عربي داخل العالم. */
UCLASS(
	ClassGroup = (ArabicText),
	HideCategories = (
		Physics,
		Collision,
		Lighting,
		HLOD,
		VirtualTexture,
		Replication,
		ComponentReplication,
		Cooking,
		UserInterface,
		Interaction,
		Animation,
		Navigation,
		Variable,
		Tick,
		Input,
		Networking,
		MaterialParameters,
		TextureStreaming,
		Mobile,
		RayTracing,
		AssetUserData
		),
	meta = (
		BlueprintSpawnableComponent,
		DisplayName = "Arabic Widget Text"
		)
)
class ARABICWIDGET_API UArabicWidgetTextComponent
	: public UWidgetComponent
{
	GENERATED_BODY()

public:
	UArabicWidgetTextComponent();

	// المحتوى

	/** النص المعروض. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Content",
		meta = (
			MultiLine = "true",
			DisplayPriority = "1"
			)
	)
	FText Text;

	// المظهر

	/** الخط. None يستخدم خط المحرك. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Appearance",
		meta = (
			DisplayName = "Font (None = Engine Default)",
			DisplayPriority = "1"
			)
	)
	FSlateFontInfo Font;

	/** لون النص. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Appearance",
		meta = (
			DisplayName = "Color",
			DisplayPriority = "2"
			)
	)
	FLinearColor TextColor;

	/** إزاحة الظل. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Appearance",
		meta = (DisplayPriority = "3")
	)
	FVector2D ShadowOffset;

	/** لون الظل. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Appearance",
		meta = (DisplayPriority = "4")
	)
	FLinearColor ShadowColor;

	// الخلفية

	/** لون الخلفية. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Background",
		meta = (
			DisplayName = "Background Color",
			DisplayPriority = "1"
			)
	)
	FLinearColor PanelBackgroundColor;

	/** حشوة الخلفية. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Background",
		meta = (
			DisplayName = "Padding",
			DisplayPriority = "2"
			)
	)
	FMargin BackgroundPadding;

	// التخطيط

	/** التفاف تلقائي. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Layout",
		meta = (
			DisplayName = "Auto Wrap",
			DisplayPriority = "1"
			)
	)
	bool bAutoWrapText;

	/** عرض الالتفاف. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Layout",
		meta = (
			DisplayName = "Maximum Width",
			DisplayPriority = "2",
			ClampMin = "1.0",
			UIMin = "64.0",
			UIMax = "4096.0",
			EditCondition = "bAutoWrapText",
			EditConditionHides
			)
	)
	float MaximumTextWidth;

	/** المحاذاة. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Layout",
		meta = (
			DisplayName = "Alignment",
			DisplayPriority = "3"
			)
	)
	EArabicWidgetTextAlignment HorizontalAlignment;

	/** اتجاه الكتابة. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Layout",
		meta = (
			DisplayName = "Direction",
			DisplayPriority = "4"
			)
	)
	EArabicWidgetTextDirection TextDirection;

	// الوجهان

	/** وضع الوجه الخلفي. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Two Sided",
		meta = (
			DisplayName = "Mode",
			DisplayPriority = "1"
			)
	)
	EArabicWidgetTextTwoSidedMode TwoSidedMode;

	/** نفس ألوان الوجه الأمامي. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Two Sided",
		meta = (
			DisplayName = "Use Front Colors",
			DisplayPriority = "2",
			EditCondition =
			"TwoSidedMode != EArabicWidgetTextTwoSidedMode::Off",
			EditConditionHides
			)
	)
	bool bMatchFrontAppearance;

	/** لون نص الخلف. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Two Sided",
		meta = (
			DisplayName = "Back Text Color",
			DisplayPriority = "3",
			EditCondition =
			"TwoSidedMode != EArabicWidgetTextTwoSidedMode::Off && !bMatchFrontAppearance",
			EditConditionHides
			)
	)
	FLinearColor BackTextColor;

	/** لون خلفية الخلف. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Two Sided",
		meta = (
			DisplayName = "Back Background Color",
			DisplayPriority = "4",
			EditCondition =
			"TwoSidedMode != EArabicWidgetTextTwoSidedMode::Off && !bMatchFrontAppearance",
			EditConditionHides
			)
	)
	FLinearColor BackPanelBackgroundColor;

	// الكاميرا

	/** وضع مواجهة الكاميرا. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Camera",
		meta = (
			DisplayName = "Face Camera",
			DisplayPriority = "1"
			)
	)
	EArabicWidgetTextFaceCameraMode FaceCameraMode;

	/** رقم اللاعب. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		AdvancedDisplay,
		Category = "Arabic Widget Text|Camera",
		meta = (
			DisplayName = "Player Index",
			DisplayPriority = "2",
			ClampMin = "0",
			EditCondition =
			"FaceCameraMode != EArabicWidgetTextFaceCameraMode::Off",
			EditConditionHides
			)
	)
	int32 CameraPlayerIndex;

	/** إزاحة الدوران. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		AdvancedDisplay,
		Category = "Arabic Widget Text|Camera",
		meta = (
			DisplayName = "Rotation Offset",
			DisplayPriority = "3",
			EditCondition =
			"FaceCameraMode != EArabicWidgetTextFaceCameraMode::Off",
			EditConditionHides
			)
	)
	FRotator FaceCameraRotationOffset;

	// الأداء

	/** مسافة العرض. صفر بلا حد. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Performance",
		meta = (
			DisplayName = "Max Render Distance",
			DisplayPriority = "1",
			ClampMin = "0.0",
			UIMin = "0.0",
			UIMax = "100000.0"
			)
	)
	float MaxRenderDistance;

	// واجهة Blueprint

	/** يغيّر النص. */
	UFUNCTION(BlueprintCallable, Category = "Arabic Widget Text")
	void SetWorldText(const FText& NewText);

	/** يغيّر مواجهة الكاميرا. */
	UFUNCTION(BlueprintCallable, Category = "Arabic Widget Text")
	void SetFaceCameraMode(EArabicWidgetTextFaceCameraMode NewMode);

	/** يغيّر وضع الوجهين. */
	UFUNCTION(BlueprintCallable, Category = "Arabic Widget Text")
	void SetTwoSidedMode(EArabicWidgetTextTwoSidedMode NewMode);

	/** يحدّث النص. */
	UFUNCTION(BlueprintCallable, Category = "Arabic Widget Text")
	void RefreshWorldText();

	/** يزامن خامة الوجهين. */
	virtual void SetMaterial(
		int32 ElementIndex,
		UMaterialInterface* Material
	) override;

	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

protected:
	virtual void OnRegister() override;
	virtual void OnUnregister() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(
		FPropertyChangedEvent& PropertyChangedEvent
	) override;

	virtual void PostEditUndo() override;
#endif

private:
	/** يحدّث المكوّن. */
	void RefreshComponent();

	/** يبني سطح النص. */
	void RebuildSurface(
		UWidgetComponent* Surface,
		const FLinearColor& SurfaceTextColor,
		const FLinearColor& SurfaceBackgroundColor,
		bool bMirrorHorizontally
	);

	/** يحدّث الوجه الخلفي. */
	void UpdateBackSurface();
	void CreateBackSurface();
	void SyncBackSurface();
	void SyncBackMaterial();
	void DestroyBackSurface();

	/** يحدّث إعدادات الأداء. */
	void SyncPerformanceSettings();

	/** يطلب إعادة الرسم. */
	void RequestSurfaceUpdate(UWidgetComponent* Surface);

	/** يزامن وضع الكاميرا. */
	void SyncFaceCameraMode();

	/** يوجّه النص للكاميرا. */
	void UpdateFaceCamera();

	/** سطح الوجه الخلفي. */
	UPROPERTY(
		Transient,
		DuplicateTransient,
		TextExportTransient
	)
	TObjectPtr<UWidgetComponent> BackWidgetComponent;

	EArabicWidgetTextFaceCameraMode AppliedFaceCameraMode;
	FRotator SavedRelativeRotation;
	bool bHasSavedRelativeRotation;
};
