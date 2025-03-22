// Fill out your copyright notice in the Description page of Project Settings.

#include "Unit.h"

#include "AshesOfWar/AbilitySystem/AOWAbilitySystemComponent.h"
#include "AshesOfWar/AbilitySystem/AOWAttributeSet.h"
#include "AshesOfWar/AI/AIControllers/UnitAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AUnit::AUnit() {
  PrimaryActorTick.bCanEverTick = true;
}

void AUnit::BeginPlay()
{
  Super::BeginPlay();
  AbilitySystemComponent->InitAbilityActorInfo(this, this);
  // Give the ability to a unit should be done in the server
  GiveDefaultAbilities();
  // Initialize the default attributes of the unit
  InitDefaultAttributes();
  // Setup the AI controller
  AIControllerClass = AUnitAIController::StaticClass();
  if (AIControllerClass)
  {
    AUnitAIController* AIController = GetWorld()->SpawnActor<AUnitAIController>(AIControllerClass, FTransform::Identity);
    AIController->Possess(this);
  }
}

UAbilitySystemComponent* AUnit::GetAbilitySystemComponent() const
{
  return AbilitySystemComponent;
}

UAOWAttributeSet* AUnit::GetAttributeSet() const
{
  return AttributeSet;
}

void AUnit::MoveToLocation(FVector TargetLocation)
{
  if (AAIController* AIController = Cast<AAIController>(GetController()))
  {
    // set the speed of the unit to the speed unit, and move to the target location
    GetCharacterMovement()->MaxWalkSpeed = NUMERIC_VALUE(AttributeSet, Speed);
    AIController->MoveToLocation(TargetLocation);
  }
}

void AUnit::StopMovement()
{
  if (AAIController* AIController = Cast<AAIController>(GetController()))
  {
    AIController->StopMovement();
  }
}

void AUnit::GiveDefaultAbilities()
{
  check(AbilitySystemComponent);

  // should check if it is the server
  // if (!HasAuthority()) return;

  // give the default abilities to the unit and initialize them with level 1
  for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
  {
    int32 InitLevel = 1;
    const FGameplayAbilitySpec AbilitySpec(AbilityClass, InitLevel);
    AbilitySystemComponent->GiveAbility(AbilitySpec);
  }
}

void AUnit::InitDefaultAttributes()
{
  // Use the DefaultAttributeEffect to initialize the attributes of the unit
  // This would 
  if (!AbilitySystemComponent || !DefaultAttributeEffect) return;

  FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
  EffectContext.AddSourceObject(this);

  float Level =  1.0f;
  const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
    DefaultAttributeEffect, Level, EffectContext);

  if (SpecHandle.IsValid())
  {
    AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
  }
}


