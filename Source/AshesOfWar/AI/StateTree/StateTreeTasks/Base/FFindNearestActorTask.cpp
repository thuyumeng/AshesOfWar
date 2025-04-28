#include "FFindNearestActorTask.h"
#include "VisualLogger/VisualLogger.h"
#include "StateTreeExecutionContext.h"
#include "StateTreePropertyBindings.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "GameplayStateTree"

EStateTreeRunStatus FStateTreeFindNearestActorTask::EnterState(FStateTreeExecutionContext& Context,
                                                               const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	if (!InstanceData.Actor)
	{
		UE_VLOG(Context.GetOwner(), LogStateTree, Error, TEXT("FStateTreeFindNearestActorTask failed since Context Actor is missing."));
		return EStateTreeRunStatus::Failed;
	}
	UWorld* World = Context.GetWorld();
	// Get All the actors of the specified class within the search radius
	GetNearestActorOfClass(World, InstanceData.TargetActorClass, InstanceData.FoundActor, InstanceData.SearchRadius, InstanceData.Actor);
	return EStateTreeRunStatus::Unset;
}

void FStateTreeFindNearestActorTask::ExitState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	UE_VLOG(Context.GetOwner(), LogStateTree, Log, TEXT("FStateTreeFindNearestActorTask Exit"));
}

void FStateTreeFindNearestActorTask::GetNearestActorOfClass(const UWorld* World, const TSubclassOf<AActor>& ActorClass,
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

#if WITH_EDITOR
FText FStateTreeFindNearestActorTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView,
	const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	check(InstanceData);

	FText TargetClassText = BindingLookup.GetBindingSourceDisplayName(
		FStateTreePropertyPath(
			ID,
			GET_MEMBER_NAME_CHECKED(FInstanceDataType, TargetActorClass)
		), Formatting);

	if (Formatting == EStateTreeNodeFormatting::RichText)
	{
		return FText::Format(LOCTEXT("FindNearestActor", "<b>Target Actor Class</> {0}"),TargetClassText);
	}
	return FText::Format(LOCTEXT("FindNearestActor", "Target Actor Class {0}"), TargetClassText);
}
#endif // WITH_EDITOR

#undef LOCTEXT_NAMESPACE