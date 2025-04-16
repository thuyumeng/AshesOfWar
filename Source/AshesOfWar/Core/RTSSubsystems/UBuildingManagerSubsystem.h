#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UBuildingManagerSubsystem.generated.h"

UCLASS()
class ASHESOFWAR_API UBuildingManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	//* Ajouter : Méthode TryPlaceBuildingAtLocation() *//
	//* Gérer la preview (ghost), les collisions, les vérifications de coût *//
};