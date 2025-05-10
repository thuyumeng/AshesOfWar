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


public:
// ------------------ Resource Collection ------------------
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void MineResource();

	UFUNCTION(BlueprintCallable, Category = "Resource")
	void StopMining();
	
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void SetCurrentResourceNode(AAResourceNode* NewNode);

	UFUNCTION(BlueprintCallable, Category = "Resource")
	AActor* GetCurrentDepositTarget() const;

	UFUNCTION(BlueprintCallable, Category = "Resource")
	AActor* GetCurrentResourceTarget() const;

	UFUNCTION(BlueprintCallable, Category = "Resource")
	UResourceComponent* GetResourceComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Resource")
	void DepositAtBase();

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

// ------------------ Internal Logic ------------------
protected:
	virtual void InitAttributeSets() override;

// ------------------ Components ------------------
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (AllowPrivateAccess = "true"))
	UResourceComponent* ResourceComponent;

// ------------------ Construction Data ------------------
protected:
	UPROPERTY()
	TArray<AActor*> ActiveConstructionTargets;
	
	UPROPERTY()
	APlayerState* OwningPlayerState = nullptr;
};