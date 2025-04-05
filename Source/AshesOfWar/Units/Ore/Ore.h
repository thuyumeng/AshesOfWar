// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "Ore.generated.h"

UCLASS()
class ASHESOFWAR_API AOre : public AUnit
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOre() = default;

protected:
	// the customized OnBeginPlay function
	virtual void OnBeginPlay_Implementation() override;
};
