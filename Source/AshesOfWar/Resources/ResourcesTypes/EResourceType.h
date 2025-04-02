// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EResourceType.generated.h"

/**
 * Enum representing the three types of resources used in the game.
 */
UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Aetherium UMETA(DisplayName = "Aetherium"),  // Basic resource, used for most production
	Vitae     UMETA(DisplayName = "Vitae"),      // Mid-tier resource, used for units and tech
	Umbra     UMETA(DisplayName = "Umbra")       // Advanced resource, used for upgrades and late game
};
