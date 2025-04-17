#include "FlyingBase.h"

#include "AshesOfWar/Buildings/Base/EBuildingType.h"
#include "AshesOfWar/Buildings/Component/UUnitProductionComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h" // pour EResourceType

AFlyingBase::AFlyingBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Ajout du composant de production d'unités
	UnitProductionComponent = CreateDefaultSubobject<UUnitProductionComponent>(TEXT("UnitProductionComponent"));

	// Configuration de base du BuildingData
	BuildingData.RequiredTechTier = 1;
	BuildingData.ConstructionTime = 45.f;
	BuildingData.MaxHealth = 1500.f;
	BuildingData.BuildingType = EBuildingType::HQ;

	// Gestion des coûts (dans FBuildingInfo, on suppose que tu as une map pour les coûts de ressources)
	BuildingData.ResourceCost.Add(EResourceType::Aetherium, 500);
}

void AFlyingBase::BeginPlay()
{
	Super::BeginPlay();

	// Sauvegarde la position initiale pour l'effet de lévitation
	InitialZ = GetActorLocation().Z;
}

void AFlyingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Oscillation pour simuler un vol stationnaire
	FVector Location = GetActorLocation();
	float TimeSeconds = GetWorld()->GetTimeSeconds();
	Location.Z = InitialZ + FMath::Sin(TimeSeconds * LevitationSpeed) * LevitationAmplitude;
	SetActorLocation(Location);
}

void AFlyingBase::ProduceUnit(TSubclassOf<AUnit> UnitClass)
{
	if (UnitProductionComponent && UnitClass)
	{
		UnitProductionComponent->StartProduction(UnitClass);
	}
}
