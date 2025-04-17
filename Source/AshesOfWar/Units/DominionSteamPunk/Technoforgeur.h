#pragma once

#include "CoreMinimal.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"
#include "Technoforgeur.generated.h"

/**
 * Technoforgeur
 * Unité spéciale Steampunk : récolteur, constructeur, réparateur.
 */
UCLASS()
class ASHESOFWAR_API ATechnoforgeur : public AMiner
{
	GENERATED_BODY()

public:
	ATechnoforgeur();

protected:
	virtual void BeginPlay() override;

	// Fonction pour démarrer la réparation automatique (optionnelle si avec Timer)
	void StartRepairAura();

	// Fonction appelée périodiquement pour soigner les alliés proches
	void RepairNearbyAllies();

protected:
	// Timer pour l'aura de réparation
	FTimerHandle RepairAuraTimerHandle;

	// Rayon d'effet pour trouver les alliés mécaniques
	UPROPERTY(EditDefaultsOnly, Category = "Repair")
	float RepairRadius = 400.f;

	// Quantité de vie réparée par tick
	UPROPERTY(EditDefaultsOnly, Category = "Repair")
	float RepairAmountPerSecond = 5.f;
};
