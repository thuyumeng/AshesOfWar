#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UResearchComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ASHESOFWAR_API UResearchComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//* Ajouter : Liste des recherches disponibles *//
	//* Ajouter : Méthode StartResearch(FName ResearchID) *//
	//* Ajouter : Référence à GameState pour effets globaux *//
};