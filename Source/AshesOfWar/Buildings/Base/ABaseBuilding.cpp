// Fill out your copyright notice in the Description page of Project Settings.

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

// ✅ Implémentation de l'interface

void ABaseBuilding::OnConstructed()
{
	UE_LOG(LogTemp, Log, TEXT("Bâtiment %s est maintenant construit."), *GetName());
}

void ABaseBuilding::OnDamaged(float DamageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("Bâtiment %s a subi %.1f dégâts."), *GetName(), DamageAmount);
}

void ABaseBuilding::OnRepaired(float RepairAmount)
{
	UE_LOG(LogTemp, Log, TEXT("Bâtiment %s a été réparé de %.1f points."), *GetName(), RepairAmount);
}
