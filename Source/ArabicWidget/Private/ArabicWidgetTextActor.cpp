#include "ArabicWidgetTextActor.h"
#include "ArabicWidgetTextComponent.h"

// مكوّن النص هو الجذر.
AArabicWidgetTextActor::AArabicWidgetTextActor()
{
	PrimaryActorTick.bCanEverTick = false;

	ArabicWidgetTextComponent =
		CreateDefaultSubobject<UArabicWidgetTextComponent>(
			TEXT("ArabicWidgetText")
		);

	SetRootComponent(ArabicWidgetTextComponent);
}
