// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveAttributeSet.h"

UMoveAttributeSet::UMoveAttributeSet()
{
	Speed = 20.0f;
	MaxSpeed = 100.0f;
}

void UMoveAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
