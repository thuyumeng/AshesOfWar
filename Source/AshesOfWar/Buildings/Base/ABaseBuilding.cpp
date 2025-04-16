// ABaseBuilding.cpp

#include "ABaseBuilding.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerState.h"

ABaseBuilding::ABaseBuilding()
{
	// Activer Tick uniquement si nécessaire
	PrimaryActorTick.bCanEverTick = false;

	// Composant racine par défaut
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	// Mesh visuel du bâtiment
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(SceneRoot);

	// Collision
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(SceneRoot);

	// Initialisation de la progression de construction
	ConstructionProgress = 0.0f;

	// OwningPlayer sera assigné à l’instance par le système de construction
	OwningPlayer = nullptr;
}

void ABaseBuilding::SetOwningPlayer(APlayerState* player)
{
	OwningPlayer = player;
}
