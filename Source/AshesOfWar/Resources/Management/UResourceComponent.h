#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "UResourceComponent.generated.h"

// Forward declaration
class AAResourceNode;

/**
 * UResourceComponent
 * 
 * Optional component that can be attached to units (typically workers)
 * to handle resource collection and deposit logic.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASHESOFWAR_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Constructor
	UResourceComponent();

	/** Starts collecting resources from the currently assigned resource node. */
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void BeginCollection();

	/** Stops the collection process and clears the current resource node. */
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void StopCollection();

	/** Deposits the carried resources into the player's stockpile (calls GameState logic). */
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void DepositResources();

	/** Returns the PlayerState of the owning pawn. */
	APlayerState* GetPlayerState() const;

	/** Sets the current resource node to extract resources from. */
	void SetCurrentResourceNode(AAResourceNode* NewNode);

	/** Gets the current resource node assigned. */
	AAResourceNode* GetCurrentResourceNode() const;

	/** Checks whether the unit is currently collecting resources. */
	bool IsCollecting() const;

private:
	/** Whether this unit is actively collecting resources. */
	bool bIsCollecting;

	/** Type of resource currently being carried. */
	EResourceType CarriedResourceType;

	/** Current amount of resource being carried. */
	int32 CarriedAmount;

	/** Maximum carrying capacity of this unit. */
	int32 CarriedMaxCapacity;

	/** Current resource node being mined from. */
	UPROPERTY()
	AAResourceNode* CurrentResourceNode;
};
