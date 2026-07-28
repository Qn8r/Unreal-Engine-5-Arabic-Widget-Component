#if WITH_DEV_AUTOMATION_TESTS

#include "ArabicWidgetTextComponent.h"
#include "Engine/Font.h"
#include "Engine/FontFace.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FArabicWidgetTextComponentDefaultsTest,
	"ArabicWidget.Component.Defaults",
	EAutomationTestFlags::EditorContext |
	EAutomationTestFlags::EngineFilter
)

bool FArabicWidgetTextComponentDefaultsTest::RunTest(
	const FString& Parameters
)
{
	UWorld* World =
		FAutomationEditorCommonUtils::CreateNewMap();

	AActor* Owner =
		World ? World->SpawnActor<AActor>() : nullptr;

	UArabicWidgetTextComponent* Component =
		Owner
		? NewObject<UArabicWidgetTextComponent>(Owner)
		: nullptr;

	TestNotNull(TEXT("Test world can be constructed"), World);
	TestNotNull(TEXT("Component owner can be constructed"), Owner);
	TestNotNull(TEXT("Component can be constructed"), Component);

	if (!Component)
	{
		return false;
	}

	TestEqual(
		TEXT("Widget renders in world space"),
		Component->GetWidgetSpace(),
		EWidgetSpace::World
	);

	TestTrue(
		TEXT("Widget sizes itself to its text"),
		Component->GetDrawAtDesiredSize()
	);

	TestTrue(
		TEXT("Default Arabic font is valid"),
		Component->Font.HasValidFont()
	);

	TestEqual(
		TEXT("Text direction defaults to automatic"),
		Component->TextDirection,
		EArabicWidgetTextDirection::Auto
	);

	TestEqual(
		TEXT("Two-sided rendering defaults off"),
		Component->TwoSidedMode,
		EArabicWidgetTextTwoSidedMode::Off
	);

	TestEqual(
		TEXT("Camera-facing defaults off"),
		Component->FaceCameraMode,
		EArabicWidgetTextFaceCameraMode::Off
	);

	TestEqual(
		TEXT("Collision defaults off"),
		Component->GetCollisionEnabled(),
		ECollisionEnabled::NoCollision
	);

	TestFalse(
		TEXT("Component does not affect navigation"),
		Component->CanEverAffectNavigation()
	);

	TestFalse(
		TEXT("Component does not tick on dedicated servers"),
		Component->PrimaryComponentTick.bAllowTickOnDedicatedServer
	);

	const FString ArabicSample = TEXT("مرحباً بالعالم");
	Component->SetWorldText(FText::FromString(ArabicSample));

	TestEqual(
		TEXT("Arabic text survives the Blueprint setter"),
		Component->Text.ToString(),
		ArabicSample
	);

	Component->SetFaceCameraMode(
		EArabicWidgetTextFaceCameraMode::YawOnly
	);

	TestEqual(
		TEXT("Camera-facing setter updates the mode"),
		Component->FaceCameraMode,
		EArabicWidgetTextFaceCameraMode::YawOnly
	);

	Component->SetTwoSidedMode(
		EArabicWidgetTextTwoSidedMode::ReadableBack
	);

	TestEqual(
		TEXT("Two-sided setter updates the mode"),
		Component->TwoSidedMode,
		EArabicWidgetTextTwoSidedMode::ReadableBack
	);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FArabicWidgetBundledFontsTest,
	"ArabicWidget.Content.BundledFonts",
	EAutomationTestFlags::EditorContext |
	EAutomationTestFlags::EngineFilter
)

bool FArabicWidgetBundledFontsTest::RunTest(
	const FString& Parameters
)
{
	const TCHAR* FontFamilies[] =
	{
		TEXT("Amiri"),
		TEXT("Cairo"),
		TEXT("Tajawal"),
		TEXT("NotoSansArabic"),
		TEXT("NotoNaskhArabic"),
		TEXT("NotoKufiArabic"),
		TEXT("ReemKufi"),
		TEXT("ReadexPro"),
		TEXT("ScheherazadeNew"),
		TEXT("Lateef"),
		TEXT("MarkaziText"),
		TEXT("Harmattan"),
		TEXT("Mada"),
		TEXT("Changa"),
		TEXT("ElMessiri"),
		TEXT("Alexandria")
	};

	for (const TCHAR* Family : FontFamilies)
	{
		const FString FontPath = FString::Printf(
			TEXT("/ArabicWidget/Fonts/%s/F_%s.F_%s"),
			Family,
			Family,
			Family
		);

		const FString FontFacePath = FString::Printf(
			TEXT("/ArabicWidget/Fonts/%s/FF_%s.FF_%s"),
			Family,
			Family,
			Family
		);

		TestNotNull(
			*FString::Printf(TEXT("%s Font loads"), Family),
			LoadObject<UFont>(nullptr, *FontPath)
		);

		TestNotNull(
			*FString::Printf(TEXT("%s Font Face loads"), Family),
			LoadObject<UFontFace>(nullptr, *FontFacePath)
		);
	}

	return true;
}

#endif
