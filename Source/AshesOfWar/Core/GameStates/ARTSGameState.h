// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "AshesOfWar/Resources/ResourcesTypes/FPlayerResourceData.h"
#include "ARTSGameState.generated.h"

/**
 * RTS Game State class for managing player resource data.
 * This class keeps track of the resources owned by each player (human or AI)
 * and provides functions to add, spend, or query resource amounts.
 */
UCLASS()
class ASHESOFWAR_API AARTSGameState : public AGameState
{
	GENERATED_BODY()

public:
	// Constructor
	AARTSGameState();

	// Initializes player resources when the game starts
	virtual void BeginPlay() override;

	// Stores resources for each player using their PlayerState as a key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	TMap<APlayerState*, FPlayerResourceData> PlayerResources;

	// Adds a specific amount of a resource to a player
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void AddResource(APlayerState* Player, EResourceType ResourceType, int32 Amount);

	// Tries to spend a specific amount of a resource; returns true if the player has enough
	UFUNCTION(BlueprintCallable, Category = "Resource")
	bool SpendResource(APlayerState* Player, EResourceType ResourceType, int32 Amount);

	// Returns the amount of a given resource type that a player currently has
	UFUNCTION(BlueprintCallable, Category = "Resource")
	int32 GetResourceAmount(APlayerState* Player, EResourceType ResourceType) const;
};
