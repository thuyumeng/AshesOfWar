#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AAshesOfWarGameState.generated.h"

UCLASS()
class ASHESOFWAR_API AAshesOfWarGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	//* Ajouter : TMap<APlayerState*, TArray<ABaseBuilding*>> PlayerBuildings *//
	//* Ajouter : Méthodes pour GetBuildingsOfType(), GetTechTierForPlayer(), etc. *//
};