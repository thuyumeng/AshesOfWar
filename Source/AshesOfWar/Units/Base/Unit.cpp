#include "Unit.h"

// GAS and AI includes
#include "AshesOfWar/Ability/Base/AOWAbilitySystemComponent.h"
#include "AshesOfWar/Ability/Base/AOWAttributeSet.h"
#include "AshesOfWar/AI/AIControllers/UnitAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Constructor
AUnit::AUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAOWAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UAOWAttributeSet>(TEXT("AttributeSet"));
}

// Custom hook (BlueprintNativeEvent)
void AUnit::OnBeginPlay_Implementation()
{
	// Optional: add a debug log or override in blueprint
}

// Called at unit spawn
void AUnit::BeginPlay()
{
	Super::BeginPlay();

	// Initialize GAS: this unit is both the owner and avatar
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	GiveDefaultAbilities();
	InitDefaultAttributes();

	// Ensure unit has an AI controller
	AUnitAIController* AIController = GetAIController();
	if (!AIController)
	{
		AIController = GetWorld()->SpawnActor<AUnitAIController>(AUnitAIController::StaticClass(), GetActorLocation(), GetActorRotation());

		if (AIController)
		{
			AIController->Possess(this);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[Unit] Failed to spawn AIController."));
			return;
		}
	}

	OnBeginPlay();
}

// GAS requirement
UAbilitySystemComponent* AUnit::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Accessor for AttributeSet
UAOWAttributeSet* AUnit::GetAttributeSet() const
{
	return AttributeSet;
}

// Gets the unit's AI controller
TObjectPtr<AUnitAIController> AUnit::GetAIController() const
{
	if (const APawn* AsPawn = Cast<APawn>(this))
	{
		return Cast<AUnitAIController>(AsPawn->GetController());
	}
	return nullptr;
}

// Command to move to a location
void AUnit::MoveToLocation(FVector TargetLocation)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("[Unit] MoveToLocation: No AI controller found."));
		return;
	}

	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	if (!MoveComp)
	{
		UE_LOG(LogTemp, Error, TEXT("[Unit] MoveToLocation: No movement component found."));
		return;
	}

	// Update movement speed from attribute set
	const float Speed = NUMERIC_VALUE(AttributeSet, Speed);
	MoveComp->MaxWalkSpeed = Speed;

	// Move request
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation(TargetLocation);
	MoveRequest.SetAcceptanceRadius(50.f); // Adjustable per unit type

	FNavPathSharedPtr NavPath;
	const EPathFollowingRequestResult::Type MoveResult = AIController->MoveTo(MoveRequest, &NavPath);

	UE_LOG(LogTemp, Log, TEXT("[Unit] MoveToLocation → %s | Result: %d"), *TargetLocation.ToString(), (int32)MoveResult);
}

// Stops movement
void AUnit::StopMovement()
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->StopMovement();
	}
}

// Grants default gameplay abilities to the unit
void AUnit::GiveDefaultAbilities()
{
	check(AbilitySystemComponent);

	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
	{
		const int32 InitLevel = 1;
		const FGameplayAbilitySpec AbilitySpec(AbilityClass, InitLevel);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

// Initializes base stats via a default effect
void AUnit::InitDefaultAttributes()
{
	if (!AbilitySystemComponent || !DefaultAttributeEffect) return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const float Level = 1.0f;
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
		DefaultAttributeEffect, Level, EffectContext);

	if (SpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}
