#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UConstructionComponent.generated.h"

// Forward declarations
class ABaseBuilding;
class AMiner;

/**
 * UConstructionComponent
 * 
 * Component responsible for managing the construction progress of a building over time.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASHESOFWAR_API UConstructionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Constructor
	UConstructionComponent();

protected:
	/** Called when the game starts. */
	virtual void BeginPlay() override;

public:
	/**
	 * Starts construction with the specified required time.
	 */
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void BeginConstruction(float TimeRequired);

	/**
	 * Ticks the construction manually (used by external manager or game tick).
	 */
	void TickConstruction(float DeltaTime);

	/**
	 * Adds a worker (e.g., Miner) to speed up construction.
	 */
	void AddWorker(AActor* Worker);

	/**
	 * Removes a worker (e.g., if dead or leaving).
	 */
	void RemoveWorker(AActor* Worker);

	/**
	 * Returns whether construction is completed.
	 */
	UFUNCTION(BlueprintCallable, Category = "Construction")
	bool IsConstructionComplete() const;

	/**
	 * Returns the normalized construction progress (0.0 to 1.0).
	 */
	UFUNCTION(BlueprintCallable, Category = "Construction")
	float GetProgressRatio() const;

private:
	/** Total time required to complete construction (in seconds). */
	UPROPERTY(EditAnywhere, Category = "Construction")
	float TotalConstructionTime;

	/** Current accumulated construction time. */
	UPROPERTY(VisibleAnywhere, Category = "Construction")
	float CurrentProgressTime;

	/** Normalized construction progress ratio. */
	UPROPERTY(VisibleAnywhere, Category = "Construction")
	float ProgressRatio;

	/** List of active workers currently assigned to construction. */
	UPROPERTY()
	TArray<AActor*> ActiveWorkers;

	/** Whether the construction has been completed. */
	UPROPERTY(VisibleAnywhere, Category = "Construction")
	bool bIsComplete;
};
