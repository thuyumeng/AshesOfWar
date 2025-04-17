#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"
#include "UBuildingManagerSubsystem.generated.h"

// Forward declarations
class ABuildingGhostActor;

/**
 * UBuildingManagerSubsystem
 *
 * Handles building placement, resource cost verification, terrain validation,
 * and manages the spawn/clearance of building ghost previews.
 */
UCLASS()
class ASHESOFWAR_API UBuildingManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** Initializes the subsystem at GameInstance start. */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/**
	 * Attempts to place a building at a specified location.
	 * @param Location - World location where placement is attempted.
	 * @param BuildingClass - Class of the building to place.
	 * @return True if placement was successful.
	 */
	UFUNCTION(BlueprintCallable, Category = "Building")
	bool TryPlaceBuildingAtLocation(const FVector& Location, TSubclassOf<ABaseBuilding> BuildingClass);

	/**
	 * Destroys the current building ghost actor, if any.
	 */
	UFUNCTION(BlueprintCallable, Category = "Building")
	void ClearGhost();

	/**
	 * Returns the currently active ghost actor (if one exists).
	 */
	ABuildingGhostActor* GetCurrentGhost() const;

private:
	/** Class used to spawn the building ghost. */
	UPROPERTY(EditDefaultsOnly, Category = "Building")
	TSubclassOf<ABuildingGhostActor> GhostActorClass;

	/** Currently active ghost actor instance. */
	UPROPERTY()
	ABuildingGhostActor* CurrentGhost;

	/** Building class currently selected for placement by the player. */
	UPROPERTY()
	TSubclassOf<ABaseBuilding> SelectedBuildingClass;
};
