#include "ArabicWidgetDemoRoom.h"

#include "ArabicWidgetTextComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Font.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/UObjectGlobals.h"

AArabicWidgetDemoRoom::AArabicWidgetDemoRoom()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SceneRoot->SetMobility(EComponentMobility::Static);
	SetRootComponent(SceneRoot);

	CreateRoomBlock(
		TEXT("Floor"),
		FVector(0.0f, 0.0f, -25.0f),
		FVector(14.0f, 16.0f, 0.5f)
	);

	CreateRoomBlock(
		TEXT("BackWall"),
		FVector(700.0f, 0.0f, 325.0f),
		FVector(0.5f, 16.0f, 6.5f)
	);

	CreateRoomBlock(
		TEXT("LeftWall"),
		FVector(0.0f, -800.0f, 325.0f),
		FVector(14.0f, 0.5f, 6.5f)
	);

	CreateRoomBlock(
		TEXT("RightWall"),
		FVector(0.0f, 800.0f, 325.0f),
		FVector(14.0f, 0.5f, 6.5f)
	);

	RoomLight = CreateDefaultSubobject<UPointLightComponent>(
		TEXT("RoomLight")
	);
	RoomLight->SetupAttachment(SceneRoot);
	RoomLight->SetRelativeLocation(FVector(0.0f, 0.0f, 500.0f));
	RoomLight->SetIntensity(8000.0f);
	RoomLight->SetAttenuationRadius(1800.0f);
	RoomLight->SetLightColor(FLinearColor(1.0f, 0.92f, 0.78f));

	EntranceArrow = CreateDefaultSubobject<UArrowComponent>(
		TEXT("Entrance")
	);
	EntranceArrow->SetupAttachment(SceneRoot);
	EntranceArrow->SetRelativeLocation(FVector(-650.0f, 0.0f, 80.0f));
	EntranceArrow->SetArrowColor(FColor(32, 180, 220));
	EntranceArrow->ArrowSize = 2.0f;

	HeaderText = CreateDefaultSubobject<UArabicWidgetTextComponent>(
		TEXT("HeaderText")
	);
	HeaderText->SetupAttachment(SceneRoot);
	HeaderText->SetRelativeLocation(FVector(665.0f, 0.0f, 585.0f));
	HeaderText->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	HeaderText->Text = FText::FromString(
		TEXT("معرض خطوط المكوّن العربي")
	);
	HeaderText->Font.Size = 40;
	HeaderText->PanelBackgroundColor =
		FLinearColor(0.015f, 0.02f, 0.03f, 0.92f);
	HeaderText->BackgroundPadding = FMargin(16.0f, 8.0f);
	HeaderText->SetDrawAtDesiredSize(false);
	HeaderText->SetDrawSize(FVector2D(820.0f, 82.0f));

	struct FFontSampleDefinition
	{
		const TCHAR* Family;
		const TCHAR* AssetPath;
	};

	const FFontSampleDefinition FontDefinitions[] =
	{
		{ TEXT("Amiri"), TEXT("/ArabicWidget/Fonts/Amiri/F_Amiri.F_Amiri") },
		{ TEXT("Cairo"), TEXT("/ArabicWidget/Fonts/Cairo/F_Cairo.F_Cairo") },
		{ TEXT("Tajawal"), TEXT("/ArabicWidget/Fonts/Tajawal/F_Tajawal.F_Tajawal") },
		{ TEXT("Noto Sans Arabic"), TEXT("/ArabicWidget/Fonts/NotoSansArabic/F_NotoSansArabic.F_NotoSansArabic") },
		{ TEXT("Noto Naskh Arabic"), TEXT("/ArabicWidget/Fonts/NotoNaskhArabic/F_NotoNaskhArabic.F_NotoNaskhArabic") },
		{ TEXT("Noto Kufi Arabic"), TEXT("/ArabicWidget/Fonts/NotoKufiArabic/F_NotoKufiArabic.F_NotoKufiArabic") },
		{ TEXT("Reem Kufi"), TEXT("/ArabicWidget/Fonts/ReemKufi/F_ReemKufi.F_ReemKufi") },
		{ TEXT("Readex Pro"), TEXT("/ArabicWidget/Fonts/ReadexPro/F_ReadexPro.F_ReadexPro") },
		{ TEXT("Scheherazade New"), TEXT("/ArabicWidget/Fonts/ScheherazadeNew/F_ScheherazadeNew.F_ScheherazadeNew") },
		{ TEXT("Lateef"), TEXT("/ArabicWidget/Fonts/Lateef/F_Lateef.F_Lateef") },
		{ TEXT("Markazi Text"), TEXT("/ArabicWidget/Fonts/MarkaziText/F_MarkaziText.F_MarkaziText") },
		{ TEXT("Harmattan"), TEXT("/ArabicWidget/Fonts/Harmattan/F_Harmattan.F_Harmattan") },
		{ TEXT("Mada"), TEXT("/ArabicWidget/Fonts/Mada/F_Mada.F_Mada") },
		{ TEXT("Changa"), TEXT("/ArabicWidget/Fonts/Changa/F_Changa.F_Changa") },
		{ TEXT("El Messiri"), TEXT("/ArabicWidget/Fonts/ElMessiri/F_ElMessiri.F_ElMessiri") },
		{ TEXT("Alexandria"), TEXT("/ArabicWidget/Fonts/Alexandria/F_Alexandria.F_Alexandria") }
	};

	const float ColumnPositions[] =
	{
		-555.0f,
		-185.0f,
		185.0f,
		555.0f
	};

	const float RowPositions[] =
	{
		470.0f,
		340.0f,
		210.0f,
		80.0f
	};

	for (int32 Index = 0; Index < UE_ARRAY_COUNT(FontDefinitions); ++Index)
	{
		const int32 Row = Index / 4;
		const int32 Column = Index % 4;
		const FString ComponentName = FString::Printf(
			TEXT("FontSample_%02d"),
			Index + 1
		);

		CreateFontSample(
			FName(*ComponentName),
			FontDefinitions[Index].Family,
			FontDefinitions[Index].AssetPath,
			FVector(
				665.0f,
				ColumnPositions[Column],
				RowPositions[Row]
			)
		);
	}
}

UStaticMeshComponent* AArabicWidgetDemoRoom::CreateRoomBlock(
	const FName ComponentName,
	const FVector& Location,
	const FVector& Scale
)
{
	UStaticMeshComponent* Block =
		CreateDefaultSubobject<UStaticMeshComponent>(ComponentName);

	Block->SetupAttachment(SceneRoot);
	Block->SetRelativeLocation(Location);
	Block->SetRelativeScale3D(Scale);
	Block->SetMobility(EComponentMobility::Static);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(
		TEXT("/Engine/BasicShapes/Cube.Cube")
	);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> RoomMaterial(
		TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial")
	);

	if (CubeMesh.Succeeded())
	{
		Block->SetStaticMesh(CubeMesh.Object);
	}

	if (RoomMaterial.Succeeded())
	{
		Block->SetMaterial(0, RoomMaterial.Object);
	}

	RoomMeshes.Add(Block);
	return Block;
}

UArabicWidgetTextComponent* AArabicWidgetDemoRoom::CreateFontSample(
	const FName ComponentName,
	const FString& Family,
	const FString& FontAssetPath,
	const FVector& Location
)
{
	UArabicWidgetTextComponent* Sample =
		CreateDefaultSubobject<UArabicWidgetTextComponent>(ComponentName);

	Sample->SetupAttachment(SceneRoot);
	Sample->SetRelativeLocation(Location);
	Sample->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	Sample->Text = FText::FromString(
		FString::Printf(
			TEXT("%s\nأهلاً بالعالم ١٢٣"),
			*Family
		)
	);

	if (UFont* Font = LoadObject<UFont>(nullptr, *FontAssetPath))
	{
		Sample->Font = FSlateFontInfo(Font, 22);
	}

	Sample->TextDirection = EArabicWidgetTextDirection::Auto;
	Sample->HorizontalAlignment = EArabicWidgetTextAlignment::Center;
	Sample->PanelBackgroundColor =
		FLinearColor(0.015f, 0.02f, 0.03f, 0.88f);
	Sample->BackgroundPadding = FMargin(8.0f, 5.0f);
	Sample->bAutoWrapText = false;
	Sample->SetDrawAtDesiredSize(false);
	Sample->SetDrawSize(FVector2D(340.0f, 116.0f));

	FontSamples.Add(Sample);
	return Sample;
}
