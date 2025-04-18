#include "UConstructionComponent.h"
#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"

UConstructionComponent::UConstructionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Default values
	TotalConstructionTime = 10.0f;
	CurrentProgressTime = 0.0f;
	ProgressRatio = 0.0f;
	bIsComplete = false;
}

void UConstructionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UConstructionComponent::BeginConstruction(float TimeRequired)
{
	TotalConstructionTime = TimeRequired;
	CurrentProgressTime = 0.0f;
	ProgressRatio = 0.0f;
	bIsComplete = false;

	// If you want automatic ticking, you could enable ticking here:
	// PrimaryComponentTick.SetTickFunctionEnable(true);
}

void UConstructionComponent::TickConstruction(float DeltaTime)
{
	if (bIsComplete)
	{
		return;
	}

	// Count valid workers (only miners)
	int32 WorkerCount = 0;
	for (AActor* Worker : ActiveWorkers)
	{
		if (Worker && Worker->IsA<AMiner>())
		{
			WorkerCount++;
		}
	}

	// Limit maximum number of workers affecting construction speed
	WorkerCount = FMath::Clamp(WorkerCount, 0, 2);

	// Construction speed scaling with number of active workers
	const float ConstructionSpeed = FMath::Max(1, WorkerCount);

	// Update progress
	CurrentProgressTime += DeltaTime * ConstructionSpeed;
	ProgressRatio = FMath::Clamp(CurrentProgressTime / TotalConstructionTime, 0.0f, 1.0f);

	// Update owning building's visible construction progress
	if (AActor* Owner = GetOwner())
	{
		if (ABaseBuilding* Building = Cast<ABaseBuilding>(Owner))
		{
			Building->ConstructionProgress = ProgressRatio;
		}
	}

	// Check completion
	if (ProgressRatio >= 1.0f)
	{
		bIsComplete = true;
		UE_LOG(LogTemp, Log, TEXT("Construction complete."));
	}
}

void UConstructionComponent::AddWorker(AActor* Worker)
{
	if (!Worker)
	{
		return;
	}

	AMiner* Miner = Cast<AMiner>(Worker);
	if (!Miner)
	{
		UE_LOG(LogTemp, Warning, TEXT("UConstructionComponent::AddWorker - Actor is not a Miner."));
		return;
	}

	if (ActiveWorkers.Contains(Miner))
	{
		UE_LOG(LogTemp, Warning, TEXT("UConstructionComponent::AddWorker - Miner already assigned."));
		return;
	}

	if (ActiveWorkers.Num() >= 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("UConstructionComponent::AddWorker - Maximum number of workers reached (2)."));
		return;
	}

	ActiveWorkers.Add(Miner);
	UE_LOG(LogTemp, Log, TEXT("UConstructionComponent::AddWorker - Miner added."));
}

void UConstructionComponent::RemoveWorker(AActor* Worker)
{
	if (!Worker)
	{
		return;
	}

	AMiner* Miner = Cast<AMiner>(Worker);
	if (!Miner)
	{
		UE_LOG(LogTemp, Warning, TEXT("UConstructionComponent::RemoveWorker - Actor is not a Miner."));
		return;
	}

	if (ActiveWorkers.Contains(Miner))
	{
		ActiveWorkers.Remove(Miner);
		UE_LOG(LogTemp, Log, TEXT("UConstructionComponent::RemoveWorker - Miner removed."));
	}
}

bool UConstructionComponent::IsConstructionComplete() const
{
	return bIsComplete;
}

float UConstructionComponent::GetProgressRatio() const
{
	return ProgressRatio;
}
