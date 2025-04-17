#pragma once

#include "CoreMinimal.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "UObject/SoftObjectPtr.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "Miner.generated.h"

// Forward declarations
class UResourceComponent;
class AAResourceNode;
class UStateTree;
class ABaseBuilding;

/**
 * AMiner
 * 
 * Basic worker unit used for resource harvesting and building construction.
 */
UCLASS()
class ASHESOFWAR_API AMiner : public AUnit
{
	GENERATED_BODY()

public:
	// Constructor
	AMiner();

protected:
	/** Called when the unit is initialized. */
	virtual void OnBeginPlay_Implementation() override;

	/** Called every frame to update mining or depositing behaviors. */
	virtual void Tick(float DeltaTime) override;

public:
	// --- Resource Collection ---

	/** Starts mining at the assigned resource node. */
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void MineResource();

	/** Stops the mining operation. */
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void StopMining();

	/** Manually deposits currently collected resources. */
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void DepositCollectedResources();

	/** Assigns a resource node to mine from. */
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void SetCurrentResourceNode(AAResourceNode* NewNode);

	/** Returns the attached resource component. */
	UResourceComponent* GetResourceComponent() const;

	// --- Construction ---

	/** Adds a target building to help construct. */
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void AddConstructionTarget(AActor* Building);

	/** Removes a building from the active construction list. */
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void RemoveConstructionTarget(AActor* Building);

	/** Returns whether the unit is currently constructing a building. */
	UFUNCTION(BlueprintCallable, Category = "Construction")
	bool IsConstructing() const;

	// --- Deposit & Target Management ---

	/** Returns true if the miner is currently depositing resources. */
	UFUNCTION(BlueprintCallable, Category = "Resource")
	bool IsDepositing() const;

	/** Returns the current base building used for depositing resources. */
	UFUNCTION(BlueprintCallable, Category = "Resource")
	AActor* GetCurrentDepositTarget() const;

	/** Returns the current resource node the miner is assigned to. */
	UFUNCTION(BlueprintCallable, Category = "Resource")
	AActor* GetCurrentResourceTarget() const;

	/** Moves the unit towards a specified destination. */
	void MoveToLocation(const FVector& Destination);

protected:
	// --- Resource Management ---

	/** Handles active mining logic each frame. */
	void HandleMining(float DeltaTime);

	/** Handles depositing logic when returning to base. */
	void HandleDepositing(float DeltaTime);

	/** Commands the miner to move toward the nearest deposit base. */
	void MoveToDeposit();

	/** Deposits carried resources into the current base. */
	void DepositAtBase();

	/** Searches for the nearest HQ base to deposit resources. */
	void FindNearestHQBase();

protected:
	// --- Components ---

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (AllowPrivateAccess = "true"))
	UResourceComponent* ResourceComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UStateTree* MinerStateTreeAsset;

	UPROPERTY()
	TArray<AActor*> ActiveConstructionTargets;

	// --- Mining Properties ---

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	int32 CarriedCapacity = 50;

	UPROPERTY(VisibleAnywhere, Category = "Resource")
	int32 CarriedAmount = 0;

	UPROPERTY(VisibleAnywhere, Category = "Resource")
	EResourceType CarriedResourceType = EResourceType::Aetherium;

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	float MiningDistanceThreshold = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	float DepositDistanceThreshold = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	float CollectionRatePerSecond = 10.f; // Amount collected per second

	// --- Depositing ---

	UPROPERTY()
	ABaseBuilding* CurrentDepositBaseTarget;

	/** Whether the miner is in depositing mode (returning to base). */
	bool bIsDepositing = false;
};
