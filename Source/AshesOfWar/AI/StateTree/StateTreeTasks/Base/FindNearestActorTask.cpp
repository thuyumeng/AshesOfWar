#include "FindNearestActorTask.h"
#include "AshesOfWar/AI/Utils/AIHelperLibrary.h"
#include "VisualLogger/VisualLogger.h"
#include "StateTreeExecutionContext.h"
#include "StateTreePropertyBindings.h"


#define LOCTEXT_NAMESPACE "GameplayStateTree"

EStateTreeRunStatus FStateTreeFindNearestActorTask::EnterState(FStateTreeExecutionContext& Context,
                                                               const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	if (!InstanceData.Actor)
	{
		// If the context actor is missing, we cannot proceed with the task and stop the AI statetree
		UE_VLOG(Context.GetOwner(), LogStateTree, Error, TEXT("FStateTreeFindNearestActorTask failed since Context Actor is missing."));
		return EStateTreeRunStatus::Stopped;
	}
	UWorld* World = Context.GetWorld();
	// Get All the actors of the specified class within the search radius
	UAIHelperLibrary::GetNearestActorOfClass(World, InstanceData.TargetActorClass, InstanceData.FoundActor, InstanceData.SearchRadius, InstanceData.Actor);
	
	if (!InstanceData.FoundActor)
	{
		// If no actor is found, we log a warning and stop the AI statetree
		UE_VLOG(Context.GetOwner(), LogStateTree, Warning, TEXT("FStateTreeFindNearestActorTask failed to find an actor of class %s within radius %f from %s"),
			*GetNameSafe(InstanceData.TargetActorClass), InstanceData.SearchRadius, *InstanceData.Actor->GetName());
		return EStateTreeRunStatus::Stopped;
	}
	return EStateTreeRunStatus::Running;
}

void FStateTreeFindNearestActorTask::ExitState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	UE_VLOG(Context.GetOwner(), LogStateTree, Log, TEXT("FStateTreeFindNearestActorTask Exit"));
}

#if WITH_EDITOR
FText FStateTreeFindNearestActorTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView,
	const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	check(InstanceData);

	FText ShowName;
	if (!InstanceData->TargetActorClass)
	{
		ShowName = FText::FromString("None");
	}
	else
	{
		ShowName = FText::FromString(InstanceData->TargetActorClass->GetName()); 
	}
	if (Formatting == EStateTreeNodeFormatting::RichText)
	{
		return FText::Format(LOCTEXT("FindNearestActor", "<b>FindNearestActor:Target Actor Class</> {0}"), ShowName);
	}
	return FText::Format(LOCTEXT("FindNearestActor", "FindNearestActor:Target Actor Class {0}"), ShowName);
}
#endif // WITH_EDITOR

#undef LOCTEXT_NAMESPACE