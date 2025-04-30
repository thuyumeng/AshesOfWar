// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIHelperLibrary.generated.h"

/**
 * The utils library that can be used by other AI related functions or classes
 */
UCLASS()
class ASHESOFWAR_API UAIHelperLibrary : public UAIBlueprintHelperLibrary
{
	GENERATED_BODY()
public:
	/** 
	 * This function will find the nearest actor of the specified class within the given radius
	 * from the context actor. It will ignore the context actor itself.
	 * @param World The world context in which to search for actors.
	 * @param ActorClass The class of actors to search for.
	 * @param OutActor The found actor, if any.
	 * @param Radius The search radius.
	 * @param ContextActor The actor from which to measure the distance.
	 */
	static AIMODULE_API void GetNearestActorOfClass(const UWorld* World, const TSubclassOf<AActor>& ActorClass, TObjectPtr<AActor>& OutActor, float Radius, const TObjectPtr<AActor>& ContextActor);
};
