#include "UUnitProductionComponent.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

UUnitProductionComponent::UUnitProductionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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

	if (!bIsProducing) return;

	TimeRemaining -= DeltaTime;

	if (TimeRemaining <= 0.0f && CurrentUnitClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			// Calcule une position de spawn devant le bâtiment (à ajuster selon tes préférences)
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 300.f;
			const FRotator SpawnRotation = FRotator::ZeroRotator;

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AUnit* NewUnit = World->SpawnActor<AUnit>(CurrentUnitClass, SpawnLocation, SpawnRotation, SpawnParams);

			if (NewUnit)
			{
				UE_LOG(LogTemp, Log, TEXT("[Production] Unité produite : %s"), *NewUnit->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("[Production] Échec lors du spawn de l’unité."));
			}
		}

		// Réinitialisation
		bIsProducing = false;
		TimeRemaining = 0.0f;
		TotalProductionTime = 0.0f;
		CurrentUnitClass = nullptr;
	}
}

void UUnitProductionComponent::StartProduction(TSubclassOf<AUnit> UnitClass)
{
	if (!UnitClass || bIsProducing) return;

	CurrentUnitClass = UnitClass;

	// Tu peux plus tard lire un GameplayTag ou Metadata ici pour personnaliser le temps
	TotalProductionTime = 5.0f; // temporaire : fixe pour maintenant
	TimeRemaining = TotalProductionTime;

	bIsProducing = true;

	UE_LOG(LogTemp, Log, TEXT("[Production] Début production : %s (%.1fs)"),
		*UnitClass->GetName(), TotalProductionTime);
}

void UUnitProductionComponent::CancelProduction()
{
	if (bIsProducing)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Production] Production annulée."));

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
