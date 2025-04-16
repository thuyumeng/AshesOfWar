#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UConstructionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ASHESOFWAR_API UConstructionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Constructeur
	UConstructionComponent();

protected:
	// Appelé au début du jeu
	virtual void BeginPlay() override;

public:
	// Démarre la construction du bâtiment
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void BeginConstruction(float TimeRequired);

	// Appelé à chaque tick (ou à intervalles contrôlés) pour faire progresser la construction
	void TickConstruction(float DeltaTime);

	// Ajoute un ouvrier participant à la construction (optionnel si applicable)
	void AddWorker(AActor* Worker);

	// Retire un ouvrier (ex. : s’il meurt ou s’en va)
	void RemoveWorker(AActor* Worker);

	// Vérifie si la construction est terminée
	UFUNCTION(BlueprintCallable, Category = "Construction")
	bool IsConstructionComplete() const;

	// Renvoie la progression actuelle (0.0f à 1.0f)
	UFUNCTION(BlueprintCallable, Category = "Construction")
	float GetProgressRatio() const;

private:
	// Temps requis total pour construire ce bâtiment (secondes)
	UPROPERTY(EditAnywhere, Category = "Construction")
	float TotalConstructionTime;

	// Temps actuel de construction accumulé
	UPROPERTY(VisibleAnywhere, Category = "Construction")
	float CurrentProgressTime;

	// Progression normalisée (0 à 1)
	UPROPERTY(VisibleAnywhere, Category = "Construction")
	float ProgressRatio;

	// Liste des ouvriers actifs participant à la construction
	UPROPERTY()
	TArray<AActor*> ActiveWorkers;

	// Est-ce que la construction est terminée ?
	UPROPERTY(VisibleAnywhere, Category = "Construction")
	bool bIsComplete;
};
