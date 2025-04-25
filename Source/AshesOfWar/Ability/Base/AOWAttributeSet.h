#pragma once

// --- Includes ---
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AOWAttributeSet.generated.h"

// --- Macros ---
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define NUMERIC_VALUE(AttributeSetName, PropertyName) \
	AttributeSetName->Get##PropertyName##Attribute().GetNumericValue(AttributeSetName)

/**
 * UAOWAttributeSet
 * 
 * Defines all base attributes used in Ashes of War for units and heroes.
 * Attributes include Health, Damage, Speed, Defense, and more.
 */
UCLASS()
class ASHESOFWAR_API UAOWAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	// --- Constructor ---
	UAOWAttributeSet();

	// --- Replication ---
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// --- GAS Lifecycle ---
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// --- Health Attributes ---
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAOWAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAOWAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_HealthRegen)
	FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS(UAOWAttributeSet, HealthRegen)

	// --- Movement ---
	UPROPERTY(BlueprintReadOnly, Category = "Speed", ReplicatedUsing = OnRep_Speed)
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UAOWAttributeSet, Speed)

	// --- Damage ---
	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackDamage)
	FGameplayAttributeData AttackDamage;
	ATTRIBUTE_ACCESSORS(UAOWAttributeSet, AttackDamage)

	// --- Defense ---
	UPROPERTY(BlueprintReadOnly, Category = "Defense", ReplicatedUsing = OnRep_DefenseRating)
	FGameplayAttributeData DefenseRating;
	ATTRIBUTE_ACCESSORS(UAOWAttributeSet, DefenseRating)

	// --- Replication Notifications ---
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_HealthRegen(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_Speed(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_AttackDamage(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_DefenseRating(const FGameplayAttributeData& OldValue) const;
};
