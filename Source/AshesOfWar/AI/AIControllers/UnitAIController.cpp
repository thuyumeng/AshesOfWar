// AI Controller implementation for RTS unit behavior

#include "UnitAIController.h"

// Include the StateTree component used by the AI controller
#include "AshesOfWar/AI/StateTree/UnitStateTreeAIComponent.h"

// Constructor – initializes the AI controller and adds a StateTree component
AUnitAIController::AUnitAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Enables Tick() on this actor. Disable if not needed for performance.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach the custom StateTree AI component
	UnitStateTreeAIComponent = CreateDefaultSubobject<UUnitStateTreeAIComponent>(TEXT("UnitStateTreeAI"));
}

// Called when the game starts or this controller is spawned
void AUnitAIController::BeginPlay()
{
	Super::BeginPlay();

	// You can initialize the StateTree AI logic or behavior bindings here
}
