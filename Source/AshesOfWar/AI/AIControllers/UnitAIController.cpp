// --- Includes ---
#include "UnitAIController.h"
#include "AshesOfWar/AI/StateTree/UnitStateTreeAIComponent.h"

// --- Constructor ---
AUnitAIController::AUnitAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the StateTree AI component
	UnitStateTreeAIComponent = CreateDefaultSubobject<UUnitStateTreeAIComponent>(TEXT("UnitStateTreeAIComponent"));
}

// --- BeginPlay ---
void AUnitAIController::BeginPlay()
{
	Super::BeginPlay();

	// Essential error log (only kept log)
	if (!UnitStateTreeAIComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("❌ UnitAIController: Missing UnitStateTreeAIComponent!"));
	}
}

// --- Public Getter ---
UUnitStateTreeAIComponent* AUnitAIController::GetUnitStateTreeAIComponent() const
{
	return UnitStateTreeAIComponent;
}
