#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "UResourceComponent.generated.h"

/**
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

	// Starts collecting from the current resource node
	UFUNCTION(Category = "Resource")
	void BeginCollection();

	// Stops the collection process and clears current resource node
	UFUNCTION(Category = "Resource")
	void StopCollection();

	// Deposits the carried resources into a base/building (to be implemented)
	UFUNCTION(Category = "Resource")
	void DepositResources();

	// Returns the player state of the owner pawn
	APlayerState* GetPlayerState() const;

	// Définit le node depuis lequel extraire
	void SetCurrentResourceNode(class AAResourceNode* NewNode);
	
	AAResourceNode* GetCurrentResourceNode() const;
	
	bool IsCollecting() const;

private:
	// Whether this unit is currently collecting
	bool bIsCollecting;

	// Type of resource currently being carried
	EResourceType CarriedResourceType;

	// Current amount of resource being carried
	int32 CarriedAmount;

	// Maximum amount this unit can carry
	int32 CarriedMaxCapacity;

	// Current node from which this unit is collecting resources
	UPROPERTY()
	class AAResourceNode* CurrentResourceNode;
};
