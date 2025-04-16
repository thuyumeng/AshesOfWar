#include "UConstructionComponent.h"

#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h" // Nécessaire pour vérifier le type AMiner

// Constructeur
UConstructionComponent::UConstructionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	TotalConstructionTime = 10.0f;
	CurrentProgressTime = 0.0f;
	ProgressRatio = 0.0f;
	bIsComplete = false;
}

// BeginPlay
void UConstructionComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Démarre la construction avec un temps donné
void UConstructionComponent::BeginConstruction(float TimeRequired)
{
	TotalConstructionTime = TimeRequired;

	CurrentProgressTime = 0.0f;
	ProgressRatio = 0.0f;
	bIsComplete = false;

	// Si tu veux une progression automatique : active le tick ici
	// PrimaryComponentTick.SetTickFunctionEnable(true);
}

// Mise à jour manuelle (ex: appelée à chaque tick global ou par un manager)
void UConstructionComponent::TickConstruction(float DeltaTime)
{
	if (bIsComplete) return;

	// Compte les mineurs valides
	int32 WorkerCount = 0;
	for (AActor* Worker : ActiveWorkers)
	{
		if (Worker && Worker->IsA<AMiner>())
		{
			WorkerCount++;
		}
	}

	// Limite le nombre de travailleurs à 2 maximum
	WorkerCount = FMath::Clamp(WorkerCount, 0, 2);

	// Vitesse de construction basée sur le nombre de mineurs
	float ConstructionSpeed = FMath::Max(1, WorkerCount);

	CurrentProgressTime += DeltaTime * ConstructionSpeed;
	ProgressRatio = FMath::Clamp(CurrentProgressTime / TotalConstructionTime, 0.0f, 1.0f);

	// Met à jour la progression dans le bâtiment propriétaire
	if (AActor* Owner = GetOwner())
	{
		if (ABaseBuilding* Building = Cast<ABaseBuilding>(Owner))
		{
			Building->ConstructionProgress = ProgressRatio;
		}
	}

	if (ProgressRatio >= 1.0f)
	{
		bIsComplete = true;
		UE_LOG(LogTemp, Log, TEXT("Construction terminée."));
	}
}


// Ajoute un ouvrier (doit être un AMiner)
void UConstructionComponent::AddWorker(AActor* Worker)
{
	if (!Worker) return;

	AMiner* Miner = Cast<AMiner>(Worker);
	if (!Miner)
	{
		UE_LOG(LogTemp, Warning, TEXT("UConstructionComponent::AddWorker - L'acteur n'est pas un travailleur."));
		return;
	}

	if (ActiveWorkers.Contains(Miner))
	{
		UE_LOG(LogTemp, Warning, TEXT("UConstructionComponent::AddWorker - travailleur déjà assigné."));
		return;
	}

	if (ActiveWorkers.Num() >= 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("UConstructionComponent::AddWorker - Nombre maximum de travailleurs atteint (2)."));
		return;
	}

	ActiveWorkers.Add(Miner);
	UE_LOG(LogTemp, Log, TEXT("UConstructionComponent::AddWorker - travailleur ajouté."));
}


// Retire un ouvrier (doit être un AMiner)
void UConstructionComponent::RemoveWorker(AActor* Worker)
{
	if (!Worker) return;

	AMiner* Miner = Cast<AMiner>(Worker);
	if (!Miner)
	{
		UE_LOG(LogTemp, Warning, TEXT("UConstructionComponent::RemoveWorker - L'acteur n'est pas un travailleur."));
		return;
	}

	if (ActiveWorkers.Contains(Miner))
	{
		ActiveWorkers.Remove(Miner);
		UE_LOG(LogTemp, Log, TEXT("UConstructionComponent::RemoveWorker - travailleur retiré."));
	}
}

// Vérifie si la construction est complétée
bool UConstructionComponent::IsConstructionComplete() const
{
	return bIsComplete;
}

// Retourne un ratio de 0.0 à 1.0
float UConstructionComponent::GetProgressRatio() const
{
	return ProgressRatio;
}
