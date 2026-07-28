#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArabicWidgetTextActor.generated.h"

class UArabicWidgetTextComponent;

/** Actor جاهز للوضع ويحتوي مكوّن النص العربي. */
UCLASS(
	BlueprintType,
	Blueprintable,
	HideCategories = (
		Replication,
		Networking,
		Input,
		Collision,
		Physics,
		HLOD,
		Cooking
		),
	meta = (DisplayName = "Arabic Widget Text Actor")
)
class ARABICWIDGET_API AArabicWidgetTextActor : public AActor
{
	GENERATED_BODY()

public:
	AArabicWidgetTextActor();

	/** مكوّن النص العربي العالمي المبني على Widget. */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Arabic Widget Text",
		meta = (DisplayName = "Text Component")
	)
	TObjectPtr<UArabicWidgetTextComponent> ArabicWidgetTextComponent;
};
