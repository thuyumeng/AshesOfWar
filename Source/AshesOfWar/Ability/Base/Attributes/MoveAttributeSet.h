// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetMacro.h"
#include "MoveAttributeSet.generated.h"

/**
 *  the AttributeSet containing movement-related attributes
 *  containing attributes speed , max_speed
 */
UCLASS()
class ASHESOFWAR_API UMoveAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	// Constructor
	UMoveAttributeSet();

	// Required for replication of attributes
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Current Speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FGameplayAttributeData Speed;

	// Max Speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FGameplayAttributeData MaxSpeed;

	ATTRIBUTE_ACCESSORS(UMoveAttributeSet, Speed);
	ATTRIBUTE_ACCESSORS(UMoveAttributeSet, MaxSpeed);
};
