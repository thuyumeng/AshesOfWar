#pragma once

// --- Includes ---
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "AResourceNode.generated.h"

// --- Forward Declarations ---
class UStaticMeshComponent;
class USphereComponent;

/**
 * AAResourceNode
 * 
 * Base class for all resource nodes in the RTS (Aetherium, Vitae, Umbra).
 * These represent static resources that can be harvested by units.
 */
UCLASS()
class ASHESOFWAR_API AAResourceNode : public AActor
{
	GENERATED_BODY()

public:
	// --- Constructor ---
	AAResourceNode();

	// --- Resource Logic ---
	int GetQteDisponible();
	int GetExtRate();
	void SetQteDisponible(int Amount);
	void ConsumeResource(float Amount);
	EResourceType GetResourceType() const;

protected:
	// --- Components ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource")
	UStaticMeshComponent* ResourceMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource")
	USphereComponent* CollectionRadius;

	// --- Properties ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	EResourceType ResourceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	int32 QteDisponible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	int32 ExtractionRate;
};

// --- Inline Accessor ---
inline EResourceType AAResourceNode::GetResourceType() const
{
	return ResourceType;
}
