#include "UUnitProductionComponent.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// --- Constructor ---
UUnitProductionComponent::UUnitProductionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bIsProducing = false;
	TimeRemaining = 0.f;
	TotalProductionTime = 0.f;
}

// --- Lifecycle Hooks ---
void UUnitProductionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UUnitProductionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsProducing) return;

	TimeRemaining -= DeltaTime;

	if (TimeRemaining <= 0.f && CurrentUnitClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 300.f;
			const FRotator SpawnRotation = FRotator::ZeroRotator;

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AUnit* NewUnit = World->SpawnActor<AUnit>(CurrentUnitClass, SpawnLocation, SpawnRotation, SpawnParams);

			if (NewUnit)
			{
				if (AMiner* Miner = Cast<AMiner>(NewUnit))
				{
					APlayerState* OwnerState = nullptr;

					if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
					{
						OwnerState = OwnerPawn->GetPlayerState();
					}
					else if (GetOwner()->GetInstigatorController())
					{
						OwnerState = GetOwner()->GetInstigatorController()->PlayerState;
					}

					if (OwnerState)
					{
						Miner->SetOwningPlayerState(OwnerState);
					}
					else
					{
						UE_LOG(LogTemp, Error, TEXT("[Production] Failed to assign PlayerState to unit."));
					}
				}

				UE_LOG(LogTemp, Log, TEXT("[Production] Unit produced: %s"), *NewUnit->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("[Production] Failed to spawn unit."));
			}
		}

		// Reset production state
		bIsProducing = false;
		TimeRemaining = 0.f;
		TotalProductionTime = 0.f;
		CurrentUnitClass = nullptr;
	}
}

// --- Production Control ---
void UUnitProductionComponent::StartProduction(TSubclassOf<AUnit> UnitClass)
{
	if (!UnitClass || bIsProducing) return;

	CurrentUnitClass = UnitClass;
	TotalProductionTime = 5.0f; // Temporary static value
	TimeRemaining = TotalProductionTime;
	bIsProducing = true;

	UE_LOG(LogTemp, Log, TEXT("[Production] Started: %s (%.1fs)"), *UnitClass->GetName(), TotalProductionTime);
}

void UUnitProductionComponent::CancelProduction()
{
	if (!bIsProducing) return;

	bIsProducing = false;
	TimeRemaining = 0.f;
	TotalProductionTime = 0.f;
	CurrentUnitClass = nullptr;

	UE_LOG(LogTemp, Warning, TEXT("[Production] Production canceled."));
}

bool UUnitProductionComponent::IsProducing() const
{
	return bIsProducing;
}
