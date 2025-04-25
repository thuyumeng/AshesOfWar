// --- Includes ---
#include "AOWAbilitySystemComponent.h"

// --- Constructor ---
UAOWAbilitySystemComponent::UAOWAbilitySystemComponent()
{
	// ⚠️ Tick is enabled by default for this component, but it's often unnecessary.
	// Disable it if not required to improve performance.
	PrimaryComponentTick.bCanEverTick = true;
}

// --- BeginPlay Lifecycle Function ---
void UAOWAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// 🎯 Initialization logic here (e.g., grant default abilities or apply passive gameplay effects)
}
