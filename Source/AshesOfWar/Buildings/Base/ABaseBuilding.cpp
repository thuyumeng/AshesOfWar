#include "ABaseBuilding.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerState.h"

ABaseBuilding::ABaseBuilding()
{
	// Disable ticking for better performance unless needed
	PrimaryActorTick.bCanEverTick = false;

	// Create and assign root component
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	// Create and attach building mesh to root
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(SceneRoot);

	// Create and attach collision box to root
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(SceneRoot);

	// Initialize construction progress
	ConstructionProgress = 0.0f;

	// Initially no owner assigned
	OwningPlayer = nullptr;
}

void ABaseBuilding::SetOwningPlayer(APlayerState* Player)
{
	OwningPlayer = Player;
}

// --- IBuildingInterface Implementation ---

void ABaseBuilding::OnConstructed()
{
	UE_LOG(LogTemp, Log, TEXT("Building %s has been fully constructed."), *GetName());
}

void ABaseBuilding::OnDamaged(float DamageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("Building %s has taken %.1f damage."), *GetName(), DamageAmount);
}

void ABaseBuilding::OnRepaired(float RepairAmount)
{
	UE_LOG(LogTemp, Log, TEXT("Building %s has been repaired by %.1f points."), *GetName(), RepairAmount);
}
