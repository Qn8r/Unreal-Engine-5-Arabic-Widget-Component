#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArabicWidgetDemoRoom.generated.h"

class UArabicWidgetTextComponent;
class UArrowComponent;
class UPointLightComponent;
class USceneComponent;
class UStaticMeshComponent;

/** غرفة عرض بأصول المحرك فقط. */
UCLASS(
	BlueprintType,
	Blueprintable,
	meta = (DisplayName = "Arabic Widget Demo Room")
)
class ARABICWIDGET_API AArabicWidgetDemoRoom : public AActor
{
	GENERATED_BODY()

public:
	AArabicWidgetDemoRoom();

	/** جذر الغرفة. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Demo Room")
	TObjectPtr<USceneComponent> SceneRoot;

	/** الأرضية والجدران. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Demo Room")
	TArray<TObjectPtr<UStaticMeshComponent>> RoomMeshes;

	/** عنوان المعرض. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Demo Room")
	TObjectPtr<UArabicWidgetTextComponent> HeaderText;

	/** عينات الخطوط. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Demo Room")
	TArray<TObjectPtr<UArabicWidgetTextComponent>> FontSamples;

	/** إضاءة الغرفة. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Demo Room")
	TObjectPtr<UPointLightComponent> RoomLight;

	/** جهة المدخل. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Demo Room")
	TObjectPtr<UArrowComponent> EntranceArrow;

private:
	UStaticMeshComponent* CreateRoomBlock(
		FName ComponentName,
		const FVector& Location,
		const FVector& Scale
	);

	UArabicWidgetTextComponent* CreateFontSample(
		FName ComponentName,
		const FString& Family,
		const FString& FontAssetPath,
		const FVector& Location
	);
};
