// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AResourceNode.generated.h"

//*Classe de base pour les gisements de ressources physiques (Aetherium, Vitae, Umbra)*//
UCLASS()
class ASHESOFWAR_API AAResourceNode : public AActor
{
	GENERATED_BODY()
	
public:	
	AResourceNode();

	//*Composants à ajouter : Mesh, Collision, etc.*//
	// UStaticMeshComponent* Mesh;
	// USphereComponent* CollectionRadius;

	//*Propriétés :*//
	// - Type de ressource (EResourceType)
	// - Quantité disponible (int32)
	// - Taux d’extraction

};




