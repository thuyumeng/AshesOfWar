#include "UBuildingAuraComponent.h"
#include "AbilitySystemComponent.h"
#include "AshesOfWar/Ability/Base/AOWAttributeSet.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "CollisionShape.h"
#include "CollisionQueryParams.h"
#include "PhysicsEngine/BodyInstance.h" // Important pour FOverlapResult
#include "Kismet/KismetSystemLibrary.h" // 🔁 pour SphereOverlapActors

UBuildingAuraComponent::UBuildingAuraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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
	if (!AuraEffect) return;

	UWorld* World = GetWorld();
	if (!World) return;

	TArray<AActor*> OverlappingActors;

	UKismetSystemLibrary::SphereOverlapActors(
		this,
		GetOwner()->GetActorLocation(),
		AuraRadius,
		TArray<TEnumAsByte<EObjectTypeQuery>>{ UEngineTypes::ConvertToObjectType(ECC_Pawn) },
		AActor::StaticClass(),
		TArray<AActor*>{ GetOwner() },
		OverlappingActors
	);

	TArray<AActor*> NewAffected;

	for (AActor* Actor : OverlappingActors)
	{
		if (!Actor) continue;

		if (UAbilitySystemComponent* ASC = Actor->FindComponentByClass<UAbilitySystemComponent>())
		{
			const UAOWAttributeSet* AttrSet = ASC->GetSet<UAOWAttributeSet>();
			if (AttrSet && AttrSet->GetHealth() > 0.f)
			{
				NewAffected.Add(Actor);

				if (!AffectedUnits.Contains(Actor))
				{
					ASC->ApplyGameplayEffectToSelf(
						AuraEffect->GetDefaultObject<UGameplayEffect>(),
						1.f,
						ASC->MakeEffectContext()
					);
				}
			}
		}
	}

	AffectedUnits = NewAffected;
}