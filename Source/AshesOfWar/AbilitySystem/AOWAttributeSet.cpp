// Fill out your copyright notice in the Description page of Project Settings.


#include "AOWAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAOWAttributeSet::UAOWAttributeSet()
{
}

void UAOWAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // write something like this
    // DOREPLIFETIME_CONDITION_NOTIFY(UAOWAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

void UAOWAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
    // You can add something like this to clamp the value of the attribute
    // if(Attribute == GetHealthAttribute())
    // {
    //     NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
    // }
}

void UAOWAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    // You can add something like this to clamp the value of the attribute
    if(Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
    }
}


void UAOWAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAOWAttributeSet, Health, OldHealth);
}

void UAOWAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAOWAttributeSet, MaxHealth, OldMaxHealth);
}

void UAOWAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAOWAttributeSet, HealthRegen, OldHealthRegen);
}

void UAOWAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldSpeed) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAOWAttributeSet, Speed, OldSpeed);
}

void UAOWAttributeSet::OnRep_AttackDamage(const FGameplayAttributeData& OldAttackDamage) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAOWAttributeSet, AttackDamage, OldAttackDamage);
}

