#include "UUnitProductionComponent.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Actor.h"

UUnitProductionComponent::UUnitProductionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize defaults
	bIsProducing = false;
	TimeRemaining = 0.0f;
	TotalProductionTime = 0.0f;
}

void UUnitProductionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UUnitProductionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsProducing)
	{
		return;
	}

	TimeRemaining -= DeltaTime;

	if (TimeRemaining <= 0.0f && CurrentUnitClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			// 📍 Position de spawn devant le bâtiment
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 300.0f;
			const FRotator SpawnRotation = FRotator::ZeroRotator;

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AUnit* NewUnit = World->SpawnActor<AUnit>(CurrentUnitClass, SpawnLocation, SpawnRotation, SpawnParams);

			if (NewUnit)
			{
				UE_LOG(LogTemp, Warning, TEXT("🎉 Nouvelle unité spawnée : %s"), *NewUnit->GetName());

				if (AMiner* Miner = Cast<AMiner>(NewUnit))
				{
					APlayerState* OwnerState = nullptr;

					// 🔍 Essai 1 : depuis le Pawn propriétaire
					if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
					{
						OwnerState = OwnerPawn->GetPlayerState();
						UE_LOG(LogTemp, Warning, TEXT("👤 PlayerState via OwnerPawn : %s"), OwnerState ? *OwnerState->GetName() : TEXT("nullptr"));
					}

					// 🔍 Essai 2 : via InstigatorController (en cas de bâtiment non possédé directement)
					if (!OwnerState && GetOwner()->GetInstigatorController())
					{
						OwnerState = GetOwner()->GetInstigatorController()->PlayerState;
						UE_LOG(LogTemp, Warning, TEXT("👤 PlayerState via InstigatorController : %s"), OwnerState ? *OwnerState->GetName() : TEXT("nullptr"));
					}

					// ✅ Attribution
					if (OwnerState)
					{
						Miner->SetOwningPlayerState(OwnerState);
						UE_LOG(LogTemp, Warning, TEXT("✅ PlayerState assigné au mineur : %s"), *OwnerState->GetName());
					}
					else
					{
						UE_LOG(LogTemp, Error, TEXT("❌ Aucun PlayerState trouvé pour assignation au mineur"));
					}
				}

				UE_LOG(LogTemp, Log, TEXT("[Production] Unit produced: %s"), *NewUnit->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("[Production] Failed to spawn unit."));
			}
		}

		// Réinitialisation de la production
		bIsProducing = false;
		TimeRemaining = 0.0f;
		TotalProductionTime = 0.0f;
		CurrentUnitClass = nullptr;
	}
}



void UUnitProductionComponent::StartProduction(TSubclassOf<AUnit> UnitClass)
{
	if (!UnitClass || bIsProducing)
	{
		return;
	}

	CurrentUnitClass = UnitClass;

	// TODO: Later, dynamically adjust production time based on unit metadata
	TotalProductionTime = 5.0f; // Temporary: hardcoded for now
	TimeRemaining = TotalProductionTime;

	bIsProducing = true;

	UE_LOG(LogTemp, Log, TEXT("[Production] Started production: %s (%.1f seconds)"), *UnitClass->GetName(), TotalProductionTime);
}

void UUnitProductionComponent::CancelProduction()
{
	if (bIsProducing)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Production] Production canceled."));

		bIsProducing = false;
		TimeRemaining = 0.0f;
		TotalProductionTime = 0.0f;
		CurrentUnitClass = nullptr;
	}
}

bool UUnitProductionComponent::IsProducing() const
{
	return bIsProducing;
}
