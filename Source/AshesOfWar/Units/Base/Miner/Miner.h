#pragma once

// --- Includes ---
#include "CoreMinimal.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "UObject/SoftObjectPtr.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "Miner.generated.h"

// --- Forward Declarations ---
class UResourceComponent;
class AAResourceNode;
class UStateTree;
class ABaseBuilding;

/**
 * AMiner
 * 
 * Worker unit used for gathering resources and construction.
 */
UCLASS()
class ASHESOFWAR_API AMiner : public AUnit
{
	GENERATED_BODY()

public:
	AMiner();

protected:
	virtual void OnBeginPlay_Implementation() override;
	virtual void Tick(float DeltaTime) override;

public:
	// --- Resource Collection ---
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void MineResource();

	UFUNCTION(BlueprintCallable, Category = "Resource")
	void StopMining();

	UFUNCTION(BlueprintCallable, Category = "Resource")
	void DepositCollectedResources();

	UFUNCTION(BlueprintCallable, Category = "Resource")
	void SetCurrentResourceNode(AAResourceNode* NewNode);

	UFUNCTION(BlueprintCallable, Category = "Resource")
	bool IsDepositing() const;

	UFUNCTION(BlueprintCallable, Category = "Resource")
	AActor* GetCurrentDepositTarget() const;

	UFUNCTION(BlueprintCallable, Category = "Resource")
	AActor* GetCurrentResourceTarget() const;

	UResourceComponent* GetResourceComponent() const;

	// --- Construction ---
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void AddConstructionTarget(AActor* Building);

	UFUNCTION(BlueprintCallable, Category = "Construction")
	void RemoveConstructionTarget(AActor* Building);

	UFUNCTION(BlueprintCallable, Category = "Construction")
	bool IsConstructing() const;

	// --- Ownership ---
	void SetOwningPlayerState(APlayerState* Player);
	APlayerState* GetOwningPlayerState() const;

	// --- Movement ---
	void MoveToLocation(const FVector& Destination);

protected:
	// --- Components ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (AllowPrivateAccess = "true"))
	UResourceComponent* ResourceComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UStateTree* MinerStateTreeAsset;

	UPROPERTY()
	TArray<AActor*> ActiveConstructionTargets;

	// --- Resource Data ---
	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	int32 CarriedCapacity = 50;

	UPROPERTY(VisibleAnywhere, Category = "Resource")
	float CarriedAmount = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Resource")
	EResourceType CarriedResourceType = EResourceType::Aetherium;

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	float MiningDistanceThreshold = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	float DepositDistanceThreshold = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	float CollectionRatePerSecond = 10.f;

	UPROPERTY()
	APlayerState* OwningPlayerState = nullptr;

	UPROPERTY()
	ABaseBuilding* CurrentDepositBaseTarget;

	bool bIsDepositing = false;

	// --- Internal Logic ---
	void HandleMining(float DeltaTime);
	void HandleDepositing(float DeltaTime);
	void MoveToDeposit();
	void DepositAtBase();
	void FindNearestHQBase();
};
