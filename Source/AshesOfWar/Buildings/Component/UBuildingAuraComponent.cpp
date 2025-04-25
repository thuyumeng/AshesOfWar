#include "UBuildingAuraComponent.h"
#include "AbilitySystemComponent.h"
#include "AshesOfWar/Ability/Base/Attributes/HealthAttributeSet.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/EngineTypes.h"
#include "CollisionShape.h"
#include "CollisionQueryParams.h"
#include "PhysicsEngine/BodyInstance.h"

UBuildingAuraComponent::UBuildingAuraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Default values
	AuraRadius = 500.f;
	bIsBuff = true;
}

void UBuildingAuraComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBuildingAuraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ApplyAuraToNearbyUnits();
}

void UBuildingAuraComponent::ApplyAuraToNearbyUnits()
{
	// Validate aura effect
	if (!AuraEffect)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	TArray<AActor*> OverlappingActors;

	// Perform a sphere overlap to find nearby actors (filtering for Pawns)
	UKismetSystemLibrary::SphereOverlapActors(
		this,
		GetOwner()->GetActorLocation(),
		AuraRadius,
		TArray<TEnumAsByte<EObjectTypeQuery>>{ UEngineTypes::ConvertToObjectType(ECC_Pawn) },
		AActor::StaticClass(),
		TArray<AActor*>{ GetOwner() }, // Ignore self
		OverlappingActors
	);

	TArray<AActor*> NewAffected;

	for (AActor* Actor : OverlappingActors)
	{
		if (!Actor) continue;

		// Try to find the Ability System Component
		if (UAbilitySystemComponent* ASC = Actor->FindComponentByClass<UAbilitySystemComponent>())
		{
			// Check if the unit is alive (Health > 0)
			const UHealthAttributeSet* HealthSet = ASC->GetSet<UHealthAttributeSet>();
			if (HealthSet && HealthSet->GetHealth() > 0.f)
			{
				NewAffected.Add(Actor);

				// Only apply the aura if it was not already affecting this unit
				if (!AffectedUnits.Contains(Actor))
				{
					ASC->ApplyGameplayEffectToSelf(
						AuraEffect->GetDefaultObject<UGameplayEffect>(),
						1.0f,
						ASC->MakeEffectContext()
					);
				}
			}
		}
	}

	// Update the list of affected units
	AffectedUnits = NewAffected;
}
