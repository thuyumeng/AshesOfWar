// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthAttributeSet.h"

UHealthAttributeSet::UHealthAttributeSet()
{
	Health = 100.f;
	MaxHealth = 10000.f;
	Shield = 500.f;
	MaxShield = 500.f;
	Defense = 0.f;
	Damage = 0.f;
}

void UHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	// this function must be overriden by the subclass even if you are doing the single-player game
	// or else you will get a compilation error
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}