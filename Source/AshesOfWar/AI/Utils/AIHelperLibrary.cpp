// Fill out your copyright notice in the Description page of Project Settings.


#include "AIHelperLibrary.h"

#include "Kismet/GameplayStatics.h"

void UAIHelperLibrary::GetNearestActorOfClass(const UWorld* World, const TSubclassOf<AActor>& ActorClass,
                                              TObjectPtr<AActor>& OutActor, float Radius, const TObjectPtr<AActor>& ContextActor)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(World, ActorClass, FoundActors);
	
	for (AActor* FoundActor : FoundActors)
	{
		if (FoundActor == ContextActor)
		{
			continue;
		}
		float Distance = FVector::Dist(FoundActor->GetActorLocation(), ContextActor->GetActorLocation());
		if (Distance < Radius)
		{
			Radius = Distance;
			OutActor = FoundActor;
		}
	}
}
