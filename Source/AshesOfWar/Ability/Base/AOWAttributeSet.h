// The AttributeSet of a unit in Ashes of War.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AOWAttributeSet.generated.h"

// Macro that simplifies the declaration of accessor functions for attributes.
// Example: ATTRIBUTE_ACCESSORS(UMyAttributeSet, Health) creates:
// - static FGameplayAttribute GetHealthAttribute();
// - float GetHealth() const;
// - void SetHealth(float NewVal);
// - void InitHealth(float NewVal);
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// Gets the raw numeric value of an attribute from an attribute set instance
#define NUMERIC_VALUE(AttributeSetName, PropertyName) \
AttributeSetName->Get##PropertyName##Attribute().GetNumericValue(AttributeSetName)

/**
 * UAOWAttributeSet
 * Core set of gameplay attributes (e.g., Health, Speed, Damage) replicated and used by gameplay abilities and effects.
 */
UCLASS()
class ASHESOFWAR_API UAOWAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	// Constructor
	UAOWAttributeSet();

	// Required for replication of attributes
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Called before modifying an attribute (can be used to clamp or preprocess values)
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// Called after an effect modifies an attribute (ideal for post-processing, clamping, logic)
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// ------------ Health Attributes ------------

	// Current Health
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAOWAttributeSet, Health)

	// Maximum Health
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAOWAttributeSet, MaxHealth)

	// Health Regeneration Rate (e.g., per second)
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_HealthRegen)
	FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS(UAOWAttributeSet, HealthRegen)

	// ------------ Movement ------------

	UPROPERTY(BlueprintReadOnly, Category = "Speed", ReplicatedUsing = OnRep_Speed)
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UAOWAttributeSet, Speed)

	// ------------ Damage ------------

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackDamage)
	FGameplayAttributeData AttackDamage;
	ATTRIBUTE_ACCESSORS(UAOWAttributeSet, AttackDamage)

	// ------------ Replication Notification ------------

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) const;

	UFUNCTION()
	void OnRep_Speed(const FGameplayAttributeData& OldSpeed) const;

	UFUNCTION()
	void OnRep_AttackDamage(const FGameplayAttributeData& OldAttackDamage) const;
};
