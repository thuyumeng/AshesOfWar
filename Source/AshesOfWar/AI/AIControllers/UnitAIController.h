// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "UnitAIController.generated.h"

class UUnitStateTreeAIComponent;

UCLASS()
class ASHESOFWAR_API AUnitAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	explicit AUnitAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI")
	TObjectPtr<UUnitStateTreeAIComponent> UnitStateTreeAIComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
