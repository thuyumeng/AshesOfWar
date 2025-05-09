// --- Includes ---
#include "UnitStateTreeAIComponent.h"

#include "StateTree.h"

// --- Constructor ---
UUnitStateTreeAIComponent::UUnitStateTreeAIComponent()
{
	// Ticking is disabled by default — enable only if you need per-frame logic
	// PrimaryComponentTick.bCanEverTick = true;
}

// --- Called at game start or when actor spawns ---
void UUnitStateTreeAIComponent::BeginPlay()
{
	Super::BeginPlay();

	// Starts execution of the current StateTree asset (set in Blueprint or dynamically)
	StartLogic();
}

// --- Set a new StateTree asset at runtime ---
void UUnitStateTreeAIComponent::SetStateTree(UStateTree* NewStateTree)
{
	StateTreeRef.SetStateTree(NewStateTree);
	InitializeComponent(); // Rebuilds internal logic based on new asset
}
