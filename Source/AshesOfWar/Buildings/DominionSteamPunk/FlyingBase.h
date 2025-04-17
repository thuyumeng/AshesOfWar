#pragma once

#include "CoreMinimal.h"
#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"
#include "FlyingBase.generated.h"

class UUnitProductionComponent;

/**
 * FlyingBase
 * HQ principal de la faction Steampunk. Permet la production de base (Miner pour l’instant).
 */
UCLASS()
class ASHESOFWAR_API AFlyingBase : public ABaseBuilding
{
	GENERATED_BODY()

public:
	// Constructeur
	AFlyingBase();

protected:
	// Appelé au début du jeu
	virtual void BeginPlay() override;

	// Tick pour l'effet de lévitation
	virtual void Tick(float DeltaTime) override;

public:
	// Lance la production d'une unité
	UFUNCTION(BlueprintCallable, Category = "Production")
	void ProduceUnit(TSubclassOf<AUnit> UnitClass);

private:
	// Composant qui gère la file de production d'unités
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Production", meta = (AllowPrivateAccess = "true"))
	UUnitProductionComponent* UnitProductionComponent;

	// Variables pour l'effet de lévitation
	UPROPERTY(EditDefaultsOnly, Category = "Flying Effect")
	float LevitationAmplitude = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "Flying Effect")
	float LevitationSpeed = 2.f;

	float InitialZ = 0.f;
};
