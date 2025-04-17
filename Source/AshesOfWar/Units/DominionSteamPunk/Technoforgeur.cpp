#include "Technoforgeur.h"
#include "AshesOfWar/Ability/Base/AOWAbilitySystemComponent.h"
#include "AshesOfWar/Ability/Base/AOWAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "AshesOfWar/Units/Base/Unit.h"

ATechnoforgeur::ATechnoforgeur()
{
	// Le GameplayEffect appliqué dans BeginPlay va définir ses vraies stats
}

void ATechnoforgeur::BeginPlay()
{
	Super::BeginPlay();

	// Initialisation des attributs via DefaultAttributeEffect (déjà dans Unit)
	// Le Techno aura ses propres valeurs

	// Démarrer la réparation automatique
	StartRepairAura();
}

void ATechnoforgeur::StartRepairAura()
{
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
			float Distance = FVector::Dist(GetActorLocation(), AllyUnit->GetActorLocation());
			if (Distance <= RepairRadius)
			{
				UAOWAbilitySystemComponent* ASC = Cast<UAOWAbilitySystemComponent>(AllyUnit->GetAbilitySystemComponent());
				if (ASC)
				{
					const UAOWAttributeSet* ConstAttrSet = ASC->GetSet<UAOWAttributeSet>();
					if (ConstAttrSet)
					{
						// Caster vers non-const pour pouvoir modifier
						UAOWAttributeSet* AttrSet = const_cast<UAOWAttributeSet*>(ConstAttrSet);

						float CurrentHP = AttrSet->GetHealth();
						float MaxHP = AttrSet->GetMaxHealth();

						if (CurrentHP < MaxHP)
						{
							float NewHealth = FMath::Min(CurrentHP + RepairAmountPerSecond, MaxHP);
							AttrSet->SetHealth(NewHealth);
						}
					}
				}
			}
		}
	}
}

