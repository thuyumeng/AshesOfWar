// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "UnitAIController.generated.h"

UCLASS()
class ASHESOFWAR_API AUnitAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	explicit AUnitAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	// Switch running the behavior tree or not, when false the unit is controlled by the authorized player
	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetBehaviorTreeActive(bool bIsActive);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> BehaviorTree {nullptr};
};
