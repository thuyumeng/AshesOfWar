#include "SetCurrentDepositBase.h"
#include "VisualLogger/VisualLogger.h"
#include "StateTreeExecutionContext.h"
#include "StateTreePropertyBindings.h"
#include "AshesOfWar/Resources/Management/UResourceComponent.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"
#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"

#define LOCTEXT_NAMESPACE "GameplayStateTree"
EStateTreeRunStatus FStateTreeSetCurrentDepositBaseTask::EnterState(FStateTreeExecutionContext& Context,
                                                               const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	AMiner* Miner = Cast<AMiner>(InstanceData.Actor);

	if (!Miner)
	{
		// If the miner is not valid, we log a warning and stop the AI statetree
		UE_VLOG(Context.GetOwner(), LogStateTree, Error, TEXT("FStateTreeSetCurrentDepositBaseTask failed since Miner is needed."));
		return EStateTreeRunStatus::Stopped;
	}
	UResourceComponent* ResourceComponent = Miner->GetResourceComponent();

	ABaseBuilding* DepositBase = Cast<ABaseBuilding>(InstanceData.DepositBase);
	if (!DepositBase)
	{
		UE_VLOG(Context.GetOwner(), LogStateTree, Error, TEXT("FStateTreeSetCurrentDepositBaseTask failed since DepositBase is needed."));
		return EStateTreeRunStatus::Stopped;
	}
	ResourceComponent->SetDepositBase(DepositBase);
	return EStateTreeRunStatus::Succeeded;
}

void FStateTreeSetCurrentDepositBaseTask::ExitState(FStateTreeExecutionContext& Context,
                                         const FStateTreeTransitionResult& Transition) const
{
	UE_VLOG(Context.GetOwner(), LogStateTree, Log, TEXT("FStateTreeSetCurrentDepositBaseTask Exit"));
}

#if WITH_EDITOR
FText FStateTreeSetCurrentDepositBaseTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView,
	const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	check(InstanceData);

	FText DepositBaseName = BindingLookup.GetBindingSourceDisplayName(
		FStateTreePropertyPath(
			ID,
			GET_MEMBER_NAME_CHECKED(FInstanceDataType, DepositBase)
		), Formatting);

	if (Formatting == EStateTreeNodeFormatting::RichText)
	{
		return FText::Format(LOCTEXT("SetResourceNode", "<b>SetDepositBase:DepositBase is </> {0}"),DepositBaseName);
	}
	return FText::Format(LOCTEXT("SetResourceNode", "SetDepositBase:DepositBase is {0}"), DepositBaseName);
}
#endif // WITH_EDITOR

#undef LOCTEXT_NAMESPACE