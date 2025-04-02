// Fill out your copyright notice in the Description page of Project Settings.

#include "AOWAbilitySystemComponent.h"

// Constructor – used to initialize the component's behavior
UAOWAbilitySystemComponent::UAOWAbilitySystemComponent() {
  // Allows this component to be ticked every frame (disable if not needed for better performance)
  PrimaryComponentTick.bCanEverTick = true;

  // ⚠️ Consider setting bCanEverTick = false if no per-frame logic is required
}

// Called when the game starts
void UAOWAbilitySystemComponent::BeginPlay() {
  // Call the parent class implementation of BeginPlay
  Super::BeginPlay();

  // You can initialize gameplay abilities, passive effects, etc., here if needed
}


