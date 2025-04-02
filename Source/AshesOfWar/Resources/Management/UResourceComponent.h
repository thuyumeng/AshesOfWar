// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UResourceComponent.generated.h"

//*Composant optionnel à attacher à un acteur pour gérer collecte ou dépôt de ressources*//
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASHESOFWAR_API UUResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UResourceComponent();

	//*Fonctions possibles :*//
	// BeginCollection(), StopCollection(), DepositResources()

		
};


