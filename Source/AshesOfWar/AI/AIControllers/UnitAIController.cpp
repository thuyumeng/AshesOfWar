#include "UnitAIController.h"
#include "AshesOfWar/AI/StateTree/UnitStateTreeAIComponent.h"

AUnitAIController::AUnitAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach the StateTree component
	UnitStateTreeAIComponent = CreateDefaultSubobject<UUnitStateTreeAIComponent>(TEXT("UnitStateTreeAIComponent"));
}

void AUnitAIController::BeginPlay()
{
	Super::BeginPlay();

	// Error log if the AI component is missing (should never happen)
	if (!UnitStateTreeAIComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("UnitAIController: UnitStateTreeAIComponent is null!"));
	}
}

UUnitStateTreeAIComponent* AUnitAIController::GetUnitStateTreeAIComponent() const
{
	return UnitStateTreeAIComponent;
}
