// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EResourceType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Aetherium UMETA(DisplayName = "Aetherium"),
	Vitae     UMETA(DisplayName = "Vitae"),
	Umbra     UMETA(DisplayName = "Umbra")
};
