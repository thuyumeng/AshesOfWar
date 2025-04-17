#pragma once

#include "CoreMinimal.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "UObject/SoftObjectPtr.h"
#include "Miner.generated.h"

class UResourceComponent;
class AAResourceNode;
class UStateTree;
class ABaseBuilding;

/**
 * AMiner
 * Base class for all units that can gather resources or construct buildings.
 */
UCLASS()
class ASHESOFWAR_API AMiner : public AUnit
{
	GENERATED_BODY()

public:
	// Constructor
	AMiner();

protected:
	// Called after BeginPlay
	virtual void OnBeginPlay_Implementation() override;

public:
	// Starts mining the current resource node
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void MineResource();

	// Stops the current mining operation
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void StopMining();

	// Deposits currently carried resources into a valid structure
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void DepositCollectedResources();

	// Sets the resource node to be mined
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void SetCurrentResourceNode(AAResourceNode* NewNode);

	// Returns the resource component of this unit
	UFUNCTION(BlueprintCallable, Category = "Resource")
	UResourceComponent* GetResourceComponent() const;

	// Adds a construction target for this miner
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void AddConstructionTarget(AActor* Building);

	// Removes a construction target when finished
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void RemoveConstructionTarget(AActor* Building);

	// Returns true if miner is currently constructing
	UFUNCTION(BlueprintCallable, Category = "Construction")
	bool IsConstructing() const;

	// Tick logic to trigger mining or construction automatically
	virtual void Tick(float DeltaTime) override;

private:
	// Component handling resource gathering logic
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (AllowPrivateAccess = "true"))
	UResourceComponent* ResourceComponent;

	// Reference to the StateTree asset used for AI behavior
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UStateTree* MinerStateTreeAsset;

	// List of active construction targets
	UPROPERTY()
	TArray<AActor*> ActiveConstructionTargets;

	// Construction settings
	UPROPERTY(EditDefaultsOnly, Category = "Construction")
	float ConstructionDistanceThreshold = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Construction")
	float ConstructionRate = 0.2f; // Progression par seconde
};
