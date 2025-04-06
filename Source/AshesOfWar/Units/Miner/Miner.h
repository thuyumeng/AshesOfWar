// A base miner class for Ashes of War's all factions
// with a basic AI state tree component and ability to collect resources
// each faction should implement its own specified miner behavior task

#pragma once

#include "CoreMinimal.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "Miner.generated.h"

UCLASS()
class ASHESOFWAR_API AMiner : public AUnit
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMiner();

protected:
	// the customized OnBeginPlay function
	virtual void OnBeginPlay_Implementation() override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
