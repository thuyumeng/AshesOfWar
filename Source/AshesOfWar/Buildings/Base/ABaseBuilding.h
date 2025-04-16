// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FBuildingInfo.h"
#include "ABaseBuilding.generated.h"

UCLASS()
class ASHESOFWAR_API ABaseBuilding : public AActor
{
	GENERATED_BODY()

public:
	// Constructeur
	ABaseBuilding();

protected:
	// Composant racine pour attacher les autres éléments
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRoot;

	// Mesh principal du bâtiment
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BuildingMesh;

	// Collision du bâtiment
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionBox;

public:
	// Données de base du bâtiment (coût, tier requis, etc.)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building")
	FBuildingInfo BuildingData;

	// Référence au joueur propriétaire
	UPROPERTY(BlueprintReadOnly, Category = "Building")
	APlayerState* OwningPlayer;

	// Pourcentage de construction (0 à 1), utilisé pour la barre de progression
	UPROPERTY(BlueprintReadOnly, Category = "Building")
	float ConstructionProgress;

	void SetOwningPlayer(APlayerState* player);
	
	// TODO :
	// * Ajouter : logique pour mettre à jour cette variable depuis le component de construction * //
};
