// Implementation of custom StateTree AI logic component

#include "UnitStateTreeAIComponent.h"

// Constructor – initialize any defaults here
UUnitStateTreeAIComponent::UUnitStateTreeAIComponent()
{
	// Ticking is disabled by default. Enable only if custom per-frame logic is added.
	// PrimaryComponentTick.bCanEverTick = true;
}

// Called when the component is first initialized (e.g., game start or actor spawn)
void UUnitStateTreeAIComponent::BeginPlay()
{
	Super::BeginPlay();

	// Start executing the StateTree behavior logic
	StartLogic();
}

// Assign a new StateTree asset and reinitialize the component
void UUnitStateTreeAIComponent::SetStateTree(UStateTree* NewStateTree)
{
	// Set the reference to the new StateTree asset
	StateTreeRef.SetStateTree(NewStateTree);

	// Reinitialize the component so it starts using the new behavior tree
	InitializeComponent();
}
