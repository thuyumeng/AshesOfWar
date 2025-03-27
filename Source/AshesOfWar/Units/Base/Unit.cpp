// Fill out your copyright notice in the Description page of Project Settings.

#include "Unit.h"

#include "AshesOfWar/Ability/AOWAbilitySystemComponent.h"
#include "AshesOfWar/Ability/AOWAttributeSet.h"
#include "AshesOfWar/AI/AIControllers/UnitAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUnit::AUnit() {
  PrimaryActorTick.bCanEverTick = true;

  AbilitySystemComponent = CreateDefaultSubobject<UAOWAbilitySystemComponent>("AbilitySystemComponent");
  AttributeSet = CreateDefaultSubobject<UAOWAttributeSet>("AttributeSet");

  // Setup the AI controller class
  AIControllerClass = AUnitAIController::StaticClass();
}

void AUnit::OnBeginPlay_Implementation()
{
  UE_LOG(LogTemp, Warning, TEXT("OnBeginPlay_Implementation"));
}

void AUnit::BeginPlay()
{
  Super::BeginPlay();

  // Initialize the ability system component
  AbilitySystemComponent->InitAbilityActorInfo(this, this);
  // Give the ability to a unit should be done in the server
  GiveDefaultAbilities();
  // Initialize the default attributes of the unit
  InitDefaultAttributes();
  // Setup the AI controller
  if (AIControllerClass)
  {
    AUnitAIController* AIController = GetWorld()->SpawnActor<AUnitAIController>(AIControllerClass, FTransform::Identity);
    AIController->Possess(this);
  }
  
  // After setting up the ability system component and the AI controller, call the OnBeginPlay function in child class
  // to customize the unit, this function can be overridden in the blueprint and C++
  OnBeginPlay();
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


