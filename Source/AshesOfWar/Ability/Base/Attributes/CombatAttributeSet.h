// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetMacro.h"
#include "CombatAttributeSet.generated.h"

/**
 * the AttributeSet containing combat-related attributes
 * contains attributes like attack damage
 */
UCLASS()
class ASHESOFWAR_API UCombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	// Constructor
	UCombatAttributeSet();

	// Required for replication of attributes
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Current attack damage
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FGameplayAttributeData AttackDamage;

	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, AttackDamage);
};
