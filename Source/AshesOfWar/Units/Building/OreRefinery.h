// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "OreRefinery.generated.h"

UCLASS()
class ASHESOFWAR_API AOreRefinery : public AUnit
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOreRefinery();

protected:
	// the customized OnBeginPlay function
	virtual void OnBeginPlay_Implementation() override;
};
