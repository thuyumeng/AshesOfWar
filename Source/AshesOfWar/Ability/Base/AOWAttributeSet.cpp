// AttributeSet logic implementation for Ashes of War

#include "AOWAttributeSet.h" // Corresponding header
#include "GameplayEffectExtension.h" // Required for PostGameplayEffectExecute context
#include "Net/UnrealNetwork.h" // For attribute replication macros

// Constructor – initialize default values here if needed
UAOWAttributeSet::UAOWAttributeSet()
{
    // No initialization needed for now; all attributes use default constructors
    Health = 100.f;
    MaxHealth = 10000.f;
    HealthRegen = 10.f;
    Speed = 500.f;
    AttackDamage = 10.f;
}

// Sets up replication for the attributes
void UAOWAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Registers each attribute to be replicated across the network with notifications
    DOREPLIFETIME_CONDITION_NOTIFY(UAOWAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAOWAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAOWAttributeSet, HealthRegen, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAOWAttributeSet, Speed, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAOWAttributeSet, AttackDamage, COND_None, REPNOTIFY_Always);
}

// Called before the value of any attribute changes
void UAOWAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    // Clamp Health to MaxHealth before the value is changed
    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
    }

    // You can add similar checks for other attributes (Speed, AttackDamage, etc.)
}

// Called after a gameplay effect has modified one or more attributes
void UAOWAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    // Clamp Health again to ensure it stays within valid bounds after modification
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
    }

    // Add more post-effect logic for other attributes if needed (e.g., healing, status effects)
}

// ----------------------------
// Replication Notification Functions
// These are called automatically on clients when an attribute's value is updated via replication
// ----------------------------

void UAOWAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
    // Notify GAS system that Health was replicated and changed
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
