#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AOWInputInterface.generated.h"

// Forward declaration
class AUnit;

/**
 * UAOWInputInterface
 * 
 * Unreal UInterface class required for defining the IAOWInputInterface.
 * No implementation required unless extending functionality.
 */
UINTERFACE()
class ASHESOFWAR_API UAOWInputInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * IAOWInputInterface
 * 
 * Interface used to define standardized input-related functions for RTS units (e.g., selection, move orders).
 * 
 * Implement this interface in any unit that needs to react to input commands.
 */
class ASHESOFWAR_API IAOWInputInterface
{
	GENERATED_BODY()

public:
	// Interface methods to be implemented by inheriting classes
	// Example:
	// virtual void MoveToLocation(const FVector& TargetLocation) = 0;
};
