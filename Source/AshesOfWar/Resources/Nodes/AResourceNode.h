#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "AResourceNode.generated.h"

/**
 * Base class for resource nodes (Aetherium, Vitae, Umbra).
 * These represent physical resource sources that can be harvested by workers.
 */
UCLASS()
class ASHESOFWAR_API AAResourceNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Constructor
	AAResourceNode();

	// Get the current available quantity
	int GetQteDisponible();

	// Get the extraction rate
	int GetExtRate();

	// Set a new available quantity
	void SetQteDisponible(int Amount);

	// Consume a given amount from the available quantity
	void ConsumeResource(float Amount);

	// Returns the resource type (Aetherium, Vitae, Umbra)
	EResourceType GetResourceType() const;

protected:

	// Static mesh for the visual appearance of the resource node
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource")
	UStaticMeshComponent* ResourceMesh;

	// Collision zone for detecting nearby worker units
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource")
	class USphereComponent* CollectionRadius;

	// The type of resource this node provides
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	EResourceType ResourceType;

	// Current available quantity of this resource
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	int32 QteDisponible;

	// How much can be extracted at once (or per second depending on mechanic)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	int32 ExtractionRate;
};

// Inline getter for the resource type
inline EResourceType AAResourceNode::GetResourceType() const
{
	return ResourceType;
}
