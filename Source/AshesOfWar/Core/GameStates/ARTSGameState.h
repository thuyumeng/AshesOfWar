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
	AARTSGameState();

	virtual void BeginPlay() override;

	// Resources per player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	TMap<APlayerState*, FPlayerResourceData> PlayerResources;

	// Ajoute une ressource au joueur
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void AddResource(APlayerState* Player, EResourceType ResourceType, int32 Amount);


	// Try to spend a resource from a player
	UFUNCTION(BlueprintCallable, Category = "Resource")
	bool SpendResource(APlayerState* Player, EResourceType ResourceType, float Amount);

	// Get resource amount
	UFUNCTION(BlueprintCallable, Category = "Resource")
	float GetResourceAmount(APlayerState* Player, EResourceType ResourceType) const;
};
