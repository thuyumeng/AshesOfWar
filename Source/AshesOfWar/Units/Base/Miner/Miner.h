#pragma once

#include "CoreMinimal.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "UObject/SoftObjectPtr.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "Miner.generated.h"

class UResourceComponent;
class AAResourceNode;
class UStateTree;
class ABaseBuilding;

/**
 * AMiner
 * Worker unit used for gathering resources and construction tasks.
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

// ------------------ Resource Collection ------------------
public:
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

// ------------------ Construction ------------------
public:
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void AddConstructionTarget(AActor* Building);

	UFUNCTION(BlueprintCallable, Category = "Construction")
	void RemoveConstructionTarget(AActor* Building);

	UFUNCTION(BlueprintCallable, Category = "Construction")
	bool IsConstructing() const;

// ------------------ Ownership ------------------
public:
	void SetOwningPlayerState(APlayerState* Player);
	APlayerState* GetOwningPlayerState() const;

// ------------------ Movement ------------------
public:
	void MoveToLocation(const FVector& Destination);

// ------------------ Internal Logic ------------------
protected:
	void HandleMining(float DeltaTime);
	void HandleDepositing(float DeltaTime);
	void MoveToDeposit();
	void DepositAtBase();
	void FindNearestHQBase();
	virtual void InitAttributeSets() override;

// ------------------ Components ------------------
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (AllowPrivateAccess = "true"))
	UResourceComponent* ResourceComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UStateTree* MinerStateTreeAsset;

// ------------------ Construction Data ------------------
protected:
	UPROPERTY()
	TArray<AActor*> ActiveConstructionTargets;
	
// ------------------ Resource Handling ------------------
protected:
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
	bool bNodeReportedEmpty = false;
	float ResourceAccumulator = 0.f;
};