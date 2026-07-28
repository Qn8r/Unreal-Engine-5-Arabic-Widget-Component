#include "ArabicWidgetTextActor.h"
#include "ArabicWidgetTextComponent.h"

// ينشئ مكوّن النص ويجعله المكوّن الجذري.
AArabicWidgetTextActor::AArabicWidgetTextActor()
{
	PrimaryActorTick.bCanEverTick = false;

	ArabicWidgetTextComponent =
		CreateDefaultSubobject<UArabicWidgetTextComponent>(
			TEXT("ArabicWidgetText")
		);

	SetRootComponent(ArabicWidgetTextComponent);
}
