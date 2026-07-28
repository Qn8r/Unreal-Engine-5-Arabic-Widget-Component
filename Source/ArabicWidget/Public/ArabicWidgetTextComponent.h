#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Fonts/SlateFontInfo.h"
#include "ArabicWidgetTextComponent.generated.h"

class UMaterialInterface;

/** محاذاة النص أفقياً. */
UENUM(BlueprintType)
enum class EArabicWidgetTextAlignment : uint8
{
	Left	UMETA(DisplayName = "Left"),
	Center	UMETA(DisplayName = "Center"),
	Right	UMETA(DisplayName = "Right")
};

/** اتجاه تدفق النص المستخدم في التشكيل والتوطين. */
UENUM(BlueprintType)
enum class EArabicWidgetTextDirection : uint8
{
	Auto			UMETA(DisplayName = "Automatic"),
	LeftToRight		UMETA(DisplayName = "Left to Right"),
	RightToLeft		UMETA(DisplayName = "Right to Left"),
	Culture			UMETA(DisplayName = "Current Game Language")
};

/** طريقة توجيه المكوّن نحو كاميرا اللاعب. */
UENUM(BlueprintType)
enum class EArabicWidgetTextFaceCameraMode : uint8
{
	Off			UMETA(DisplayName = "Off"),
	YawOnly		UMETA(DisplayName = "Yaw Only"),
	Full		UMETA(DisplayName = "Full")
};

/** طريقة عرض النص عند رؤيته من الخلف. */
UENUM(BlueprintType)
enum class EArabicWidgetTextTwoSidedMode : uint8
{
	Off				UMETA(DisplayName = "Off"),
	MirroredBack	UMETA(DisplayName = "Mirrored Back"),
	ReadableBack	UMETA(DisplayName = "Readable Back")
};

/** نص عالمي مبني على Widget، مع تشكيل عربي ودعم اتجاه RTL. */
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

	/** نص من نوع FText جاهز للتوطين ويظهر على الوجهين. */
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

	/** أصل الخط وإعداداته الطباعية. تستخدم None خط المحرك الافتراضي. */
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

	/** لون النص الأمامي وشفافيته. */
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

	/** إزاحة ظل النص بوحدات بكسل Slate. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Appearance",
		meta = (DisplayPriority = "3")
	)
	FVector2D ShadowOffset;

	/** لون ظل النص وشفافيته. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Arabic Widget Text|Appearance",
		meta = (DisplayPriority = "4")
	)
	FLinearColor ShadowColor;

	// الخلفية

	/** لون لوحة الخلفية. قيمة Alpha صفر تخفي اللوحة. */
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

	/** المسافة بين النص وحواف الخلفية. */
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

	/** يلتف النص الطويل على أسطر إضافية. */
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

	/** أقصى عرض في Slate قبل الانتقال إلى سطر جديد. */
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

	/** المحاذاة الأفقية داخل سطح النص. */
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

	/** اتجاه تدفق النص الذي يستخدمه تشكيل Slate. */
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

	/** يحدد إنشاء سطح ثانٍ خلف السطح الأمامي. */
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

	/** يطبّق ألوان الوجه الأمامي على الوجه الخلفي. */
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

	/** لون النص المخصص للوجه الخلفي. */
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

	/** لون الخلفية المخصص للوجه الخلفي. */
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

	/** يحدد دوران النص نحو كاميرا اللاعب. */
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

	/** فهرس كاميرا اللاعب المستخدمة في وضع Face Camera. */
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

	/** دوران إضافي يُطبّق بعد توجيه النص نحو الكاميرا. */
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

	/** أقصى مسافة للرسم بالسنتيمتر. الصفر يعني بلا حد. */
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

	/** يغيّر النص المحلي المعروض ويحدّث الوجهين. */
	UFUNCTION(BlueprintCallable, Category = "Arabic Widget Text")
	void SetWorldText(const FText& NewText);

	/** يغيّر وضع مواجهة الكاميرا. */
	UFUNCTION(BlueprintCallable, Category = "Arabic Widget Text")
	void SetFaceCameraMode(EArabicWidgetTextFaceCameraMode NewMode);

	/** يغيّر وضع الرسم ثنائي الوجه. */
	UFUNCTION(BlueprintCallable, Category = "Arabic Widget Text")
	void SetTwoSidedMode(EArabicWidgetTextTwoSidedMode NewMode);

	/** يعيد بناء الوجهين ورسمهما. */
	UFUNCTION(BlueprintCallable, Category = "Arabic Widget Text")
	void RefreshWorldText();

	/** يعيّن خامة Widget الأساسية ويزامن الوجه الخلفي. */
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
	/** يحدّث المحتوى والوجهين ومسافة الإخفاء وحالة إعادة الرسم. */
	void RefreshComponent();

	/** يعيد بناء سطح Widget واحد باستخدام النمط الحالي. */
	void RebuildSurface(
		UWidgetComponent* Surface,
		const FLinearColor& SurfaceTextColor,
		const FLinearColor& SurfaceBackgroundColor,
		bool bMirrorHorizontally
	);

	/** ينشئ الوجه الخلفي الاختياري أو يحدّثه أو يزيله. */
	void UpdateBackSurface();
	void CreateBackSurface();
	void SyncBackSurface();
	void SyncBackMaterial();
	void DestroyBackSurface();

	/** يطبّق إعدادات Tick وإعادة الرسم والإخفاء حسب المسافة. */
	void SyncPerformanceSettings();

	/** يطلب تحديث Render Target المخزّن فوراً. */
	void RequestSurfaceUpdate(UWidgetComponent* Surface);

	/** يحفظ الدوران أو يستعيده عند تغيير وضع Face Camera. */
	void SyncFaceCameraMode();

	/** يدوّر المكوّن نحو كاميرا اللاعب المحددة. */
	void UpdateFaceCamera();

	/** مكوّن Widget مؤقت للوجه الخلفي الاختياري. */
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
