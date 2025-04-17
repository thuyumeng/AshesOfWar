#include "FlyingBase.h"

#include "AshesOfWar/Buildings/Base/EBuildingType.h"
#include "AshesOfWar/Buildings/Component/UUnitProductionComponent.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "Components/StaticMeshComponent.h"

AFlyingBase::AFlyingBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Initialize and attach the unit production component
	UnitProductionComponent = CreateDefaultSubobject<UUnitProductionComponent>(TEXT("UnitProductionComponent"));

	// Configure base building data (costs, health, type, etc.)
	BuildingData.RequiredTechTier = 1;
	BuildingData.ConstructionTime = 45.f;
	BuildingData.MaxHealth = 1500.f;
	BuildingData.BuildingType = EBuildingType::HQ;

	// Define resource cost (example: 500 Aetherium)
	BuildingData.ResourceCost.Add(EResourceType::Aetherium, 500);
}

void AFlyingBase::BeginPlay()
{
	Super::BeginPlay();

	// Store initial Z-axis location for levitation effect
	InitialZ = GetActorLocation().Z;
}

void AFlyingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Apply a smooth sinusoidal oscillation to simulate hovering
	FVector CurrentLocation = GetActorLocation();
	float TimeSeconds = GetWorld()->GetTimeSeconds();
	CurrentLocation.Z = InitialZ + FMath::Sin(TimeSeconds * LevitationSpeed) * LevitationAmplitude;
	SetActorLocation(CurrentLocation);
}

void AFlyingBase::ProduceUnit(TSubclassOf<AUnit> UnitClass)
{
	if (UnitProductionComponent && UnitClass)
	{
		UnitProductionComponent->StartProduction(UnitClass);
	}
}
