#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UBuildingAuraComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ASHESOFWAR_API UBuildingAuraComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//* Ajouter : Portée de l’aura, type (buff/débuff), effet appliqué *//
	//* Ajouter : Vérification régulière des unités dans la zone *//
};
