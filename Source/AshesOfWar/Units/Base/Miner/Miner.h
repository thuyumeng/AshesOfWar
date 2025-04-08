#pragma once

#include "CoreMinimal.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "UObject/SoftObjectPtr.h"
#include "Miner.generated.h"

class UResourceComponent;
class AAResourceNode;
class UStateTree;

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

	// Deposits currently carried resources into a valid structure (to be implemented)
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void DepositCollectedResources();

	// Sets the resource node to be mined
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void SetCurrentResourceNode(AAResourceNode* NewNode);

	// Returns the resource component of this unit
	UFUNCTION(BlueprintCallable, Category = "Resource")
	UResourceComponent* GetResourceComponent() const;

	// Tick logic to trigger mining automatically
	virtual void Tick(float DeltaTime) override;

private:
	// Component handling resource gathering logic
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (AllowPrivateAccess = "true"))
	UResourceComponent* ResourceComponent;

	// Reference to the StateTree asset used for AI behavior
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UStateTree* MinerStateTreeAsset;
};
