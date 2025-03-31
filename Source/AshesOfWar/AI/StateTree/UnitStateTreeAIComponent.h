// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateTreeAIComponent.h"
#include "UnitStateTreeAIComponent.generated.h"


UCLASS(ClassGroup=(AI), meta=(BlueprintSpawnableComponent))
class ASHESOFWAR_API UUnitStateTreeAIComponent : public UStateTreeAIComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUnitStateTreeAIComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Call this function when switching 
	UFUNCTION(BlueprintCallable, Category = "StateTree")
	void SetStateTree(UStateTree* NewStateTree);
	
};
