#include "SetCurrentResourceNode.h"
#include "VisualLogger/VisualLogger.h"
#include "StateTreeExecutionContext.h"
#include "StateTreePropertyBindings.h"
#include "AshesOfWar/Resources/Management/UResourceComponent.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"

#define LOCTEXT_NAMESPACE "GameplayStateTree"
EStateTreeRunStatus FStateTreeSetCurrentResourceNodeTask::EnterState(FStateTreeExecutionContext& Context,
                                                               const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	AMiner* Miner = Cast<AMiner>(InstanceData.Actor);

	if (!Miner)
	{
		// If the miner is not valid, we log a warning and stop the AI statetree
		UE_VLOG(Context.GetOwner(), LogStateTree, Error, TEXT("FStateTreeSetCurrentResourceNodeTask failed since Miner is needed."));
		return EStateTreeRunStatus::Stopped;
	}
	UResourceComponent* ResourceComponent = Miner->GetResourceComponent();

	AAResourceNode* ResourceNode = Cast<AAResourceNode>(InstanceData.CurrentResource);
	if (!ResourceNode)
	{
		UE_VLOG(Context.GetOwner(), LogStateTree, Error, TEXT("FStateTreeSetCurrentResourceNodeTask failed since ResourceNode is needed."));
		return EStateTreeRunStatus::Stopped;
	}
	ResourceComponent->SetCurrentResourceNode(ResourceNode);
	return EStateTreeRunStatus::Running;
}

void FStateTreeSetCurrentResourceNodeTask::ExitState(FStateTreeExecutionContext& Context,
                                         const FStateTreeTransitionResult& Transition) const
{
	UE_VLOG(Context.GetOwner(), LogStateTree, Log, TEXT("FStateTreeSetCurrentResourceNodeTask Exit"));
}

#if WITH_EDITOR
FText FStateTreeSetCurrentResourceNodeTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView,
	const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	check(InstanceData);

	FText ResourceName = BindingLookup.GetBindingSourceDisplayName(
		FStateTreePropertyPath(
			ID,
			GET_MEMBER_NAME_CHECKED(FInstanceDataType, CurrentResource)
		), Formatting);

	if (Formatting == EStateTreeNodeFormatting::RichText)
	{
		return FText::Format(LOCTEXT("SetResourceNode", "<b>SetResourceNode:CurrentResource is </> {0}"),ResourceName);
	}
	return FText::Format(LOCTEXT("SetResourceNode", "SetResourceNode:CurrentResource is {0}"), ResourceName);
}
#endif // WITH_EDITOR

#undef LOCTEXT_NAMESPACE