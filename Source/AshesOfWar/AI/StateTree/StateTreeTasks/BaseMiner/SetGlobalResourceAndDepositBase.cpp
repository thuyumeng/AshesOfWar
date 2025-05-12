#include "SetGlobalResourceAndDepositBase.h"
#include "VisualLogger/VisualLogger.h"
#include "StateTreeExecutionContext.h"
#include "AshesOfWar/Resources/Management/UResourceComponent.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"

#define LOCTEXT_NAMESPACE "GameplayStateTree"
EStateTreeRunStatus FStateTreeSetGlobalResourceAndDepositBaseTask::EnterState(FStateTreeExecutionContext& Context,
                                                               const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	AMiner* Miner = Cast<AMiner>(InstanceData.Actor);

	if (!Miner)
	{
		// If the miner is not valid, we log a warning and stop the AI statetree
		UE_VLOG(Context.GetOwner(), LogStateTree, Error, TEXT("FStateTreeSetGlobalResourceAndDepositBaseTask failed since Miner is needed."));
		return EStateTreeRunStatus::Stopped;
	}

	// Setting the ResourceNode and DepositBase
	UResourceComponent* ResourceComponent = Miner->GetResourceComponent();
	if (!ResourceComponent)
	{
		UE_VLOG(Context.GetOwner(), LogStateTree, Error, TEXT("FStateTreeSetGlobalResourceAndDepositBaseTask failed since ResourceComponent is needed."));
		return EStateTreeRunStatus::Stopped;
	}
	
	AAResourceNode* ResourceNode  = ResourceComponent->GetCurrentResourceNode();
	bool* BIsResourceSetPtr = InstanceData.BIsResourceSet.GetMutablePtr(Context);
	*BIsResourceSetPtr = IsValid(ResourceNode);
	
	ABaseBuilding* DepositBase = ResourceComponent->GetDepositBaseTarget();
	bool* BIsDepositBaseSetPtr = InstanceData.BIsDepositBase.GetMutablePtr(Context);
	*BIsDepositBaseSetPtr = IsValid(DepositBase);

	// Succeeded means: ResourceNode and DepositBase are valid
	// Failed means: ResourceNode or DepositBase are not valid
	if (IsValid(ResourceNode) && IsValid(DepositBase))
		return EStateTreeRunStatus::Succeeded;

	if (!IsValid(ResourceNode))
	{
		UE_LOG(LogTemp,
			Warning,
			TEXT("[TEST] failed since ResourceNode is not valid. Name: %s"), *GetNameSafe(ResourceNode));
	}

	if (!IsValid(DepositBase))
	{
		UE_LOG(LogTemp, Warning, TEXT("[TEST] failed since DepositBase is not valid."));
	}
	
	return EStateTreeRunStatus::Failed;
}

void FStateTreeSetGlobalResourceAndDepositBaseTask::ExitState(FStateTreeExecutionContext& Context,
                                         const FStateTreeTransitionResult& Transition) const
{
	UE_VLOG(Context.GetOwner(), LogStateTree, Log, TEXT("FStateTreeSetGlobalResourceAndDepositBaseTask Exit"));
}

#if WITH_EDITOR
FText FStateTreeSetGlobalResourceAndDepositBaseTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView,
	const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	check(InstanceData);
	
	if (Formatting == EStateTreeNodeFormatting::RichText)
	{
		return LOCTEXT("SetGlobalResourceAndDepositBaseTask", "<b>SetGlobalResourceAndDepositBaseTask </>");
	}
	return LOCTEXT("SetGlobalResourceAndDepositBaseTask", "SetGlobalResourceAndDepositBaseTask");
}
#endif // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
