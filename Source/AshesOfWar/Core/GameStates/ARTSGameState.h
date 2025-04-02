// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "AshesOfWar/Resources/ResourcesTypes/FPlayerResourceData.h"
#include "ARTSGameState.generated.h"


//* Struct pour stocker les ressources de chaque joueur *//
// FPlayerResourceData à inclure ou forward declare si séparé

// Enum EResourceType à inclure pour identifier les types de ressource

UCLASS()
class ASHESOFWAR_API AARTSGameState : public AGameState
{
	GENERATED_BODY()

public:
// Constructeur
	AARTSGameState();

	// TMap pour stocker les ressources de chaque joueur (humain ou IA)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ressource")
	TMap<APlayerState*, FPlayerResourceData> PlayerResources;

	//* Ajoute une quantité à une ressource spécifique pour un joueur *//
	UFUNCTION(BlueprintCallable, Category = "Ressource")
	void AddResource(APlayerState* Player, EResourceType ResourceType, int32 Amount);

	//* Tente de retirer une ressource ; retourne vrai si possible *//
	UFUNCTION(BlueprintCallable, Category = "Ressource")
	bool SpendResource(APlayerState* Player, EResourceType ResourceType, int32 Amount);

	//* Retourne la quantité actuelle pour un type de ressource *//
	UFUNCTION(BlueprintCallable, Category = "Ressource")
	int32 GetResourceAmount(APlayerState* Player, EResourceType ResourceType) const;

	// Surcharge de BeginPlay pour initialiser les ressources de chaque joueur
	virtual void BeginPlay() override;

};
