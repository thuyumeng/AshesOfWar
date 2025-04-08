#include "UnitAIController.h"
#include "AshesOfWar/AI/StateTree/UnitStateTreeAIComponent.h"

AUnitAIController::AUnitAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// Crée et attache le composant StateTree avec un nom cohérent
	UnitStateTreeAIComponent = CreateDefaultSubobject<UUnitStateTreeAIComponent>(TEXT("UnitStateTreeAIComponent"));
}

void AUnitAIController::BeginPlay()
{
	Super::BeginPlay();

	// Log de debug utile
	if (!UnitStateTreeAIComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("UnitAIController: Le composant UnitStateTreeAIComponent est null !"));
	}
}

UUnitStateTreeAIComponent* AUnitAIController::GetUnitStateTreeAIComponent() const
{
	return UnitStateTreeAIComponent;
}
