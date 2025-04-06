#include "Unit.h"

// GAS and AI includes
#include "AshesOfWar/Ability/Base/AOWAbilitySystemComponent.h"
#include "AshesOfWar/Ability/Base/AOWAttributeSet.h"
#include "AshesOfWar/AI/AIControllers/UnitAIController.h"
#include "AshesOfWar/AI/StateTree/UnitStateTreeAIComponent.h"

#include "GameFramework/CharacterMovementComponent.h"


// Constructor – initialize GAS components
AUnit::AUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Ability System and Attribute Set as default subobjects
	AbilitySystemComponent = CreateDefaultSubobject<UAOWAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UAOWAttributeSet>("AttributeSet");
}

// BlueprintNativeEvent override – can be implemented in C++ or Blueprint
void AUnit::OnBeginPlay_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("OnBeginPlay_Implementation"));
}

// Called when the unit spawns in the world
void AUnit::BeginPlay()
{
	Super::BeginPlay();

	// Initialize GAS with this unit as both owner and avatar
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	// Grant base abilities and attributes (server-side logic)
	GiveDefaultAbilities();
	InitDefaultAttributes();

	// check if the unit has a valid AI controller
	AUnitAIController* AIController = GetAIController();
	if (!AIController)
	{
		// create a new AI controller if none exists
		AIController = GetWorld()->SpawnActor<AUnitAIController>(AUnitAIController::StaticClass(), GetActorLocation(), GetActorRotation());
		if (AIController)
		{
			// Possess the unit with the new AI controller
			AIController->Possess(this);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn AIController for unit!"));
			return;
		}
	}
	
	OnBeginPlay();
}

// GAS interface requirement – gives access to this unit's AbilitySystemComponent
UAbilitySystemComponent* AUnit::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Custom getter to access this unit's AttributeSet
UAOWAttributeSet* AUnit::GetAttributeSet() const
{
	return AttributeSet;
}

TObjectPtr<AUnitAIController> AUnit::GetAIController() const
{
	const APawn* AsPawn = Cast<APawn>(this);
	if (AsPawn != nullptr)
	{
		return Cast<AUnitAIController>(AsPawn->GetController());
	}
	return nullptr;
}

// Called to move the unit to a specified world location
void AUnit::MoveToLocation(FVector TargetLocation)
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		// Apply current unit speed from AttributeSet
		// Notice: must be walkable character skeletal mesh, not a static mesh!!!
		GetCharacterMovement()->MaxWalkSpeed = NUMERIC_VALUE(AttributeSet, Speed);

		// Order movement to location using AI navigation
		AIController->MoveToLocation(TargetLocation);
	}
}

// Halts movement of the unit using AIController
void AUnit::StopMovement()
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->StopMovement();
	}
}

// Grants abilities listed in DefaultAbilities to the unit
void AUnit::GiveDefaultAbilities()
{
	check(AbilitySystemComponent);

	// ❗ Optional: Only run on the server
	// if (!HasAuthority()) return;

	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
	{
		int32 InitLevel = 1; // Default level (can be dynamic later)
		const FGameplayAbilitySpec AbilitySpec(AbilityClass, InitLevel);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

// Applies the default gameplay effect that initializes unit stats (e.g., HP, Damage, Speed)
void AUnit::InitDefaultAttributes()
{
	if (!AbilitySystemComponent || !DefaultAttributeEffect) return;

	// Create context and spec for the gameplay effect
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	float Level = 1.0f; // Initial effect level

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
		DefaultAttributeEffect, Level, EffectContext);

	// Apply the effect to self
	if (SpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}
