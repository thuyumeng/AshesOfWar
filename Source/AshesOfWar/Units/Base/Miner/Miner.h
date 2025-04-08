#pragma once

#include "CoreMinimal.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "UObject/SoftObjectPtr.h"
#include "Miner.generated.h"

class UResourceComponent;
class AAResourceNode;
class UStateTree;

/**
 * AMiner
 * Classe de base pour toutes les unités pouvant récolter ou construire.
 */
UCLASS()
class ASHESOFWAR_API AMiner : public AUnit
{
	GENERATED_BODY()

public:
	// Constructeur
	AMiner();

protected:
	// Appelé après BeginPlay
	virtual void OnBeginPlay_Implementation() override;

public:
	// Déclenche la récolte de ressources
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void MineResource();

	// Arrête la récolte de ressources
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void StopMining();

	// Dépose les ressources dans une structure (fonctionnalité à compléter)
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void DepositCollectedResources();

	// Définit le node de ressource actuel
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void SetCurrentResourceNode(AAResourceNode* NewNode);

	// Accès au composant de ressource
	UFUNCTION(BlueprintCallable, Category = "Resource")
	UResourceComponent* GetResourceComponent() const;

	// Fonction appelée à chaque frame
	virtual void Tick(float DeltaTime) override;

private:
	// Composant gérant la logique de récolte
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (AllowPrivateAccess = "true"))
	UResourceComponent* ResourceComponent;

	// Référence éditable au StateTree de cette unité
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UStateTree* MinerStateTreeAsset;
};
