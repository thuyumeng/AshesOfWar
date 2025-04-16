#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"
#include "UBuildingManagerSubsystem.generated.h"

class ABuildingGhostActor;

/**
 * Gère le placement de bâtiments, la vérification des coûts, du terrain, et le spawn du ghost.
 */
UCLASS()
class ASHESOFWAR_API UBuildingManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Initialisation du subsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// Tente de placer un bâtiment à un emplacement donné
	UFUNCTION(BlueprintCallable, Category = "Building")
	bool TryPlaceBuildingAtLocation(const FVector& Location, TSubclassOf<ABaseBuilding> BuildingClass);

	// Supprime le ghost actuel (ex: si annulation)
	UFUNCTION(BlueprintCallable, Category = "Building")
	void ClearGhost();

	// Retourne l'instance active du GhostActor
	ABuildingGhostActor* GetCurrentGhost() const;

private:
	// Classe du ghost à instancier
	UPROPERTY(EditDefaultsOnly, Category = "Building")
	TSubclassOf<ABuildingGhostActor> GhostActorClass;

	// Référence au ghost actif
	UPROPERTY()
	ABuildingGhostActor* CurrentGhost;

	// Classe de bâtiment sélectionnée par le joueur
	UPROPERTY()
	TSubclassOf<ABaseBuilding> SelectedBuildingClass;
};
