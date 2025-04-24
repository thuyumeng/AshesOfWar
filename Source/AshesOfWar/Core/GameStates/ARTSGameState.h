#pragma once

// --- Includes ---
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "AshesOfWar/Resources/ResourcesTypes/FPlayerResourceData.h"
#include "ARTSGameState.generated.h"

/**
 * AARTSGameState
 * 
 * Custom GameState for RTS. Tracks player resources and provides methods to modify them.
 */
UCLASS()
class ASHESOFWAR_API AARTSGameState : public AGameState
{
	GENERATED_BODY()

public:
	// --- Constructor ---
	AARTSGameState();

	// --- Lifecycle ---
	virtual void BeginPlay() override;

	// --- Resource System ---

	/** Holds the resource counts for each player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	TMap<APlayerState*, FPlayerResourceData> PlayerResources;

	/** Adds a specified resource amount to a player */
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void AddResource(APlayerState* Player, EResourceType ResourceType, int32 Amount);

	/** Attempts to deduct a resource amount from a player. Returns true if successful. */
	UFUNCTION(BlueprintCallable, Category = "Resource")
	bool SpendResource(APlayerState* Player, EResourceType ResourceType, float Amount);

	/** Retrieves the current amount of a specific resource for a player */
	UFUNCTION(BlueprintCallable, Category = "Resource")
	float GetResourceAmount(APlayerState* Player, EResourceType ResourceType) const;
};
