// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetMacro.h"
#include "HealthAttributeSet.generated.h"

/** the AttributeSet containing health-related attributes
 *  health, max health, health regen, shield
 */
UCLASS()
class ASHESOFWAR_API UHealthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	// Constructor
	UHealthAttributeSet();

	// Required for replication of attributes
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Current health
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FGameplayAttributeData Health;
	// Upper limit for health value
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FGameplayAttributeData MaxHealth;
	// Current shield
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FGameplayAttributeData Shield;
	// Upper limit for shield value
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FGameplayAttributeData MaxShield;
	// Defense rating
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FGameplayAttributeData Defense;
 
	// Damage value calculated during a GE. Meta attribute.
	UPROPERTY(VisibleAnywhere)
	FGameplayAttributeData Damage;
 
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Shield);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MaxShield);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Damage);
};
