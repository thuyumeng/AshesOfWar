// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AOWInputInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAOWInputInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * this class is used to define the input interface for the unit
 */

class AUnit;
class ASHESOFWAR_API IAOWInputInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
