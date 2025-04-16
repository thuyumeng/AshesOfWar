#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UUnitProductionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ASHESOFWAR_API UUnitProductionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//* Ajouter : File d’attente de production, méthodes StartProduction/Cancel *//
	//* Ajouter : Vérification des ressources nécessaires *//
	//* Ajouter : Timer pour produire l’unité à la fin du délai *//
};
