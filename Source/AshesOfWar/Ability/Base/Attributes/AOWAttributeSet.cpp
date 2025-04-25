// --- Includes ---
#include "AOWAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

// --- Constructor ---
UAOWAttributeSet::UAOWAttributeSet()
{
	// Default attribute values
	Health = 100.f;
	MaxHealth = 10000.f;
	HealthRegen = 10.f;
	Speed = 500.f;
	AttackDamage = 10.f;
	DefenseRating = 0.f;
}

// --- Replication Setup ---
void UAOWAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAOWAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAOWAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAOWAttributeSet, HealthRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAOWAttributeSet, Speed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAOWAttributeSet, AttackDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAOWAttributeSet, DefenseRating, COND_None, REPNOTIFY_Always);
}

// --- Pre-Attribute Modification ---
void UAOWAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}

// --- Post-Gameplay Effect Logic ---
void UAOWAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
}

// --- Replication Notifications ---
void UAOWAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAOWAttributeSet, Health, OldValue);
}

void UAOWAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAOWAttributeSet, MaxHealth, OldValue);
}

void UAOWAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAOWAttributeSet, HealthRegen, OldValue);
}

void UAOWAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAOWAttributeSet, Speed, OldValue);
}

void UAOWAttributeSet::OnRep_AttackDamage(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAOWAttributeSet, AttackDamage, OldValue);
}

void UAOWAttributeSet::OnRep_DefenseRating(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAOWAttributeSet, DefenseRating, OldValue);
}
