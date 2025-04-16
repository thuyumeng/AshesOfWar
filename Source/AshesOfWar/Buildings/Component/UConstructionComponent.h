#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UConstructionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ASHESOFWAR_API UConstructionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//* Ajouter : Gestion du progrès de construction *//
	//* Ajouter : Méthode BeginConstruction() et TickConstruction() *//
	//* Ajouter : Support des ouvriers multiples ou construction passive *//
};
