#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FBuildingInfo.h"
#include "AshesOfWar/Buildings/Interface/IBuildingInterface.h"
#include "ABaseBuilding.generated.h"

/**
 * ABaseBuilding
 * 
 * Base class for all building actors in Ashes of War RTS game.
 * Implements basic properties like owner, construction progress, and interaction logic.
 */
UCLASS()
class ASHESOFWAR_API ABaseBuilding : public AActor, public IBuildingInterface
{
	GENERATED_BODY()

public:
	// Constructor - sets default values for this building
	ABaseBuilding();

protected:
	/** 
	 * Root scene component to which all other components are attached.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRoot;

	/** 
	 * Visual static mesh component representing the building.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BuildingMesh;

	/** 
	 * Collision box for detecting interactions and physics events.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionBox;

public:
	/**
	 * Structure holding base data for the building (cost, tier requirements, etc.).
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building")
	FBuildingInfo BuildingData;

	/**
	 * Reference to the player that owns this building.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Building")
	APlayerState* OwningPlayer;

	/**
	 * Construction progress (from 0.0 to 1.0), used for visual progress bars.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Building")
	float ConstructionProgress;

	/**
	 * Assigns the owning player for this building.
	 */
	void SetOwningPlayer(APlayerState* Player);

	// --- IBuildingInterface Implementation ---

	/** Called when the building construction is completed. */
	virtual void OnConstructed() override;

	/** Called when the building takes damage. */
	virtual void OnDamaged(float DamageAmount) override;

	/** Called when the building is repaired. */
	virtual void OnRepaired(float RepairAmount) override;
};
