#pragma once
#include "CoreMinimal.h"
#include "AshesOfWar/Buildings/Base/EBuildingType.h"
#include "GameFramework/GameStateBase.h"
#include "AAshesOfWarGameState.generated.h"

class ABaseBuilding;

UCLASS()
class ASHESOFWAR_API AAshesOfWarGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	// Liste des bâtiments possédés par chaque joueur
	UPROPERTY(BlueprintReadOnly, Category = "Building")
	TMap<TObjectPtr<APlayerState>, FPlayerBuildingArray> PlayerBuildings;

	// Ajoute un bâtiment au joueur
	UFUNCTION(BlueprintCallable, Category = "Building")
	void RegisterBuilding(APlayerState* Player, ABaseBuilding* Building);

	// Récupère tous les bâtiments d’un type donné pour un joueur
	UFUNCTION(BlueprintCallable, Category = "Building")
	TArray<ABaseBuilding*> GetBuildingsOfType(APlayerState* Player, EBuildingType Type) const;

	// Définit et retourne le Tier technologique d’un joueur
	UFUNCTION(BlueprintCallable, Category = "Building")
	int32 GetTechTierForPlayer(APlayerState* Player) const;

private:
	// Niveau technologique par joueur
	UPROPERTY()
	TMap<APlayerState*, int32> PlayerTechTier;
};