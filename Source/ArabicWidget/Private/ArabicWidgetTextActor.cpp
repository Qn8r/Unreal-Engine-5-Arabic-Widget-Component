// Copyright 2026 Qn8r. Licensed under the Apache License, Version 2.0.

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
