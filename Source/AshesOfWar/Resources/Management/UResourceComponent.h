#pragma once

// --- Includes ---
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"
#include "UResourceComponent.generated.h"

// --- Forward Declarations ---
class AAResourceNode;
class ABaseBuilding;

/**
 * UResourceComponent
 * 
 * Optional component for worker units.
 * Handles collection and deposit of resources like Aetherium, Vitae, and Umbra.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASHESOFWAR_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// --- Constructor ---
	UResourceComponent();

	// --- Collection ---
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void BeginCollection();

	UFUNCTION(BlueprintCallable, Category = "Resource")
	void UpdateCollection(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Resource")
	void StopCollection();

	UFUNCTION(BlueprintCallable, Category = "Resource")
	void DepositResources();

	// --- Accessors ---
	APlayerState* GetPlayerState() const;

	void SetCurrentResourceNode(AAResourceNode* NewNode);
	AAResourceNode* GetCurrentResourceNode() const;
	bool IsCollecting() const;

	void SetDepositBaseTarget(ABaseBuilding* NewTarget);
	ABaseBuilding* GetDepositBaseTarget() const;

protected:
	// Stop collection and trigger empty event in StateTreeAIComponent
	void StopAndTriggerEmptyEvent();
private:
	// --- State ---
	bool bIsCollecting;

	EResourceType CarriedResourceType;
	int32 CarriedAmount;
	int32 CarriedMaxCapacity;
	
	TWeakObjectPtr<AAResourceNode> CurrentResourceNode;
	TWeakObjectPtr<ABaseBuilding> CurrentDepositBaseTarget;
};
