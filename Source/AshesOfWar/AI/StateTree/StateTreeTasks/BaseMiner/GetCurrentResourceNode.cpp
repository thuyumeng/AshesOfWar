#include "GetCurrentResourceNode.h"
#include "VisualLogger/VisualLogger.h"
#include "StateTreeExecutionContext.h"
#include "StateTreePropertyBindings.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"


#define LOCTEXT_NAMESPACE "GameplayStateTree"

EStateTreeRunStatus FStateTreeGetCurrentResourceTask::EnterState(FStateTreeExecutionContext& Context,
                                                               const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	if (!InstanceData.Actor)
	{
		// If the context actor is missing, we cannot proceed with the task and stop the AI statetree
		UE_VLOG(Context.GetOwner(), LogStateTree, Error, TEXT("FStateTreeGetCurrentResourceTask failed since Context Actor is missing."));
		return EStateTreeRunStatus::Stopped;
	}
	UWorld* World = Context.GetWorld();
	// Get All the actors of the specified class within the search radius
	AMiner* Miner = Cast<AMiner>(InstanceData.Actor);
	if (!Miner)
	{
		// If the miner is not valid, we log a warning and stop the AI statetree
		UE_VLOG(Context.GetOwner(), LogStateTree, Error, TEXT("FStateTreeGetCurrentResourceTask failed since Miner is needed."));
		return EStateTreeRunStatus::Stopped;
	}
	
	InstanceData.ResourceNode = Miner->GetCurrentResourceTarget();
	if (!IsValid(InstanceData.ResourceNode))
	{
		// If the resource node is not valid, we log a warning and stop the AI statetree
		UE_VLOG(Context.GetOwner(), LogStateTree, Error, TEXT("FStateTreeGetCurrentResourceTask failed since ResourceNode is needed."));
		return EStateTreeRunStatus::Stopped;
	}
	return EStateTreeRunStatus::Running;
}

void FStateTreeGetCurrentResourceTask::ExitState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	UE_VLOG(Context.GetOwner(), LogStateTree, Log, TEXT("FStateTreeGetCurrentResourceTask Exit"));
}

#if WITH_EDITOR
FText FStateTreeGetCurrentResourceTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView,
	const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	check(InstanceData);
	
	if (Formatting == EStateTreeNodeFormatting::RichText)
	{
		return LOCTEXT("GetCurrentResourceNode", "<b>GetCurrentResourceNode</>");
	}
	return LOCTEXT("GetCurrentResourceNode", "GetCurrentResourceNode");
}
#endif // WITH_EDITOR

#undef LOCTEXT_NAMESPACE


