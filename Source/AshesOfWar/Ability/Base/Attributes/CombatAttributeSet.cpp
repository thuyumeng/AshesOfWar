// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatAttributeSet.h"

UCombatAttributeSet::UCombatAttributeSet()
{
	AttackDamage = 10.f; // Default attack damage
}

void UCombatAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
