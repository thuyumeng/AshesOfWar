// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABaseBuilding.generated.h"

UCLASS()
class ASHESOFWAR_API ABaseBuilding : public AActor
{
	GENERATED_BODY()

public:
	// Constructeur
	ABaseBuilding();

	//* Ajouter : Composants visuels (static mesh), collision, aura éventuelle *//
	//* Ajouter : Système de PV, sélection, barre de construction *//
	//* Ajouter : Référence au joueur propriétaire *//
};
