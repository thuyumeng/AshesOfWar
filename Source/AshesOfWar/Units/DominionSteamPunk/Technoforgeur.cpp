#include "Technoforgeur.h"
#include "AshesOfWar/Ability/Base/AOWAbilitySystemComponent.h"
#include "AshesOfWar/Ability/Base/Attributes/AOWAttributeSet.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "AshesOfWar/Units/Base/Unit.h"

ATechnoforgeur::ATechnoforgeur()
{
	// Custom attributes are initialized via DefaultAttributeEffect already
}

void ATechnoforgeur::BeginPlay()
{
	Super::BeginPlay();

	// Start the passive repair aura when the unit spawns
	StartRepairAura();
}

void ATechnoforgeur::StartRepairAura()
{
	// Set up a repeating timer to call RepairNearbyAllies every second
	GetWorldTimerManager().SetTimer(RepairAuraTimerHandle, this, &ATechnoforgeur::RepairNearbyAllies, 1.0f, true);
}

void ATechnoforgeur::RepairNearbyAllies()
{
	TArray<AActor*> OverlappingActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		AUnit* AllyUnit = Cast<AUnit>(Actor);
		if (AllyUnit && AllyUnit != this)
		{
			const float Distance = FVector::Dist(GetActorLocation(), AllyUnit->GetActorLocation());
			if (Distance <= RepairRadius)
			{
				// Access the Ability System Component and AttributeSet
				UAOWAbilitySystemComponent* ASC = Cast<UAOWAbilitySystemComponent>(AllyUnit->GetAbilitySystemComponent());
				if (ASC)
				{
					const UAOWAttributeSet* ConstAttrSet = ASC->GetSet<UAOWAttributeSet>();
					if (ConstAttrSet)
					{
						// Remove const to modify attributes (safe because we control the call)
						UAOWAttributeSet* AttrSet = const_cast<UAOWAttributeSet*>(ConstAttrSet);

						const float CurrentHP = AttrSet->GetHealth();
						const float MaxHP = AttrSet->GetMaxHealth();

						if (CurrentHP < MaxHP)
						{
							const float NewHealth = FMath::Min(CurrentHP + RepairAmountPerSecond, MaxHP);
							AttrSet->SetHealth(NewHealth);
						}
					}
				}
			}
		}
	}
}
