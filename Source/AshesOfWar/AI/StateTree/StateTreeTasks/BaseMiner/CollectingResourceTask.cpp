#include "CollectingResourceTask.h"
#include "VisualLogger/VisualLogger.h"
#include "StateTreeExecutionContext.h"
#include "StateTreePropertyBindings.h"
#include "AshesOfWar/Resources/Management/UResourceComponent.h"

#include "AshesOfWar/Units/Base/Miner/Miner.h"

#define LOCTEXT_NAMESPACE "GameplayStateTree"
EStateTreeRunStatus FStateTreeCollectingTask::EnterState(FStateTreeExecutionContext& Context,
                                                               const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	AMiner* Miner = Cast<AMiner>(InstanceData.Actor);

	if (!Miner)
	{
		// If the miner is not valid, we log a warning and stop the AI statetree
		UE_VLOG(Context.GetOwner(), LogStateTree, Error, TEXT("FStateTreeCollectingTask failed since Miner is needed."));
		return EStateTreeRunStatus::Stopped;
	}
	UResourceComponent* ResourceComponent = Miner->GetResourceComponent();
	ResourceComponent->BeginCollection();
	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FStateTreeCollectingTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	AMiner* Miner = Cast<AMiner>(InstanceData.Actor);

	if (!Miner)
	{
		// If the miner is not valid, we log a warning and stop the AI statetree
		UE_VLOG(Context.GetOwner(), LogStateTree, Error, TEXT("FStateTreeCollectingTask failed since Miner is needed."));
		return EStateTreeRunStatus::Stopped;
	}
	UResourceComponent* ResourceComponent = Miner->GetResourceComponent();
	ResourceComponent->UpdateCollection(DeltaTime);
	// if the miner is full with resources, we notify succeed status
	if (!ResourceComponent->IsCollecting())
	{
		return EStateTreeRunStatus::Succeeded;
	}

	return EStateTreeRunStatus::Running;
	
}

void FStateTreeCollectingTask::ExitState(FStateTreeExecutionContext& Context,
                                         const FStateTreeTransitionResult& Transition) const
{
	UE_VLOG(Context.GetOwner(), LogStateTree, Log, TEXT("FStateTreeCollectingTask Exit"));
}

#if WITH_EDITOR
FText FStateTreeCollectingTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView,
	const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	check(InstanceData);

	FText MinerName = BindingLookup.GetBindingSourceDisplayName(
		FStateTreePropertyPath(
			ID,
			GET_MEMBER_NAME_CHECKED(FInstanceDataType, Actor)
		), Formatting);

	if (Formatting == EStateTreeNodeFormatting::RichText)
	{
		return FText::Format(LOCTEXT("Collecting Resource", "<b>Collecting Resource:Miner is </> {0}"),MinerName);
	}
	return FText::Format(LOCTEXT("Collecting Resource", "Collecting Resource:Miner is {0}"), MinerName);
}
#endif // WITH_EDITOR

#undef LOCTEXT_NAMESPACE