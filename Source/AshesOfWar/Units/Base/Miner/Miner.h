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
 * Unité de base pour la récolte et la construction.
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
	// Démarre la récolte
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void MineResource();

	// Arrête la récolte
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void StopMining();

	// Dépôt manuel (ex: pour forcer via interface)
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void DepositCollectedResources();

	// Assigne un node à miner
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void SetCurrentResourceNode(AAResourceNode* NewNode);

	UResourceComponent* GetResourceComponent() const;

	// Construction
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void AddConstructionTarget(AActor* Building);
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void RemoveConstructionTarget(AActor* Building);
	UFUNCTION(BlueprintCallable, Category = "Construction")
	bool IsConstructing() const;

	// Indique si actuellement le miner est en train de déposer
	UFUNCTION(BlueprintCallable, Category = "Resource")
	bool IsDepositing() const;

	// Retourne la base cible actuelle pour déposer
	UFUNCTION(BlueprintCallable, Category = "Resource")
	AActor* GetCurrentDepositTarget() const;

	// Retourne le minerai cible actuel
	UFUNCTION(BlueprintCallable, Category = "Resource")
	AActor* GetCurrentResourceTarget() const;


protected:
	// Récolte
	void HandleMining(float DeltaTime);

	// Transport / Dépôt
	void HandleDepositing(float DeltaTime);
	void MoveToDeposit();
	void DepositAtBase();
	void FindNearestHQBase();

	// Move vers location
	void MoveToLocation(const FVector& Destination);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (AllowPrivateAccess = "true"))
	UResourceComponent* ResourceComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UStateTree* MinerStateTreeAsset;

	UPROPERTY()
	TArray<AActor*> ActiveConstructionTargets;

	// Récolte
	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	int32 CarriedCapacity = 50;

	UPROPERTY(VisibleAnywhere, Category = "Resource")
	int32 CarriedAmount = 0;

	UPROPERTY(VisibleAnywhere, Category = "Resource")
	EResourceType CarriedResourceType = EResourceType::Aetherium;

	// Mode
	bool bIsDepositing = false;

	// Dépôt
	UPROPERTY()
	ABaseBuilding* CurrentDepositBaseTarget;

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	float MiningDistanceThreshold = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	float DepositDistanceThreshold = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	float CollectionRatePerSecond = 10.f; // 10 unités/s
};
