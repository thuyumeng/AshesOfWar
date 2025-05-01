#include "CallImmediateFunctionTask.h"

#include "StateTreeExecutionContext.h"
#include "StateTreePropertyBindings.h"

#define LOCTEXT_NAMESPACE "GameplayStateTree"

EStateTreeRunStatus FStateTreeCallImmediateFunctionTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
    FStateTreeCallImmediateFunctionTaskInstanceData& InstanceData = Context.GetInstanceData(*this);
    AActor* TargetActor = InstanceData.Actor;
    const FName FunctionNameToCall = InstanceData.FunctionName;

    if (!TargetActor)
    {
        UE_LOG(LogTemp, Error, TEXT("Target Actor is null."));
        return EStateTreeRunStatus::Failed;
    }

    UClass* ActorClass = TargetActor->GetClass();
    UFunction* Function = ActorClass->FindFunctionByName(FunctionNameToCall);

    if (!Function)
    {
        UE_LOG(LogTemp, Error, TEXT("Function %s not found on actor %s."), *FunctionNameToCall.ToString(), *TargetActor->GetName());
        return EStateTreeRunStatus::Failed;
    }

    // Call the function
    TargetActor->ProcessEvent(Function, nullptr);

    if (InstanceData.bFinishTaskWhenCalled)
    {
        return EStateTreeRunStatus::Succeeded;
    }
    else
    {
        return EStateTreeRunStatus::Running;
    }
}

void FStateTreeCallImmediateFunctionTask::ExitState(FStateTreeExecutionContext& Context,
    const FStateTreeTransitionResult& Transition) const
{
    UE_VLOG(Context.GetOwner(), LogStateTree, Log, TEXT("FStateTreeCallImmediateFunctionTask Exit"));
}

#if WITH_EDITOR
FText FStateTreeCallImmediateFunctionTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
    const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
    check(InstanceData);

    FText FuncNameText = BindingLookup.GetBindingSourceDisplayName(
        FStateTreePropertyPath(
            ID,
            GET_MEMBER_NAME_CHECKED(FInstanceDataType, FunctionName)
        ), Formatting);

    if (Formatting == EStateTreeNodeFormatting::RichText)
    {
        return FText::Format(LOCTEXT("CallImmediateFunction", "<b>CallImmediateFunction:/> {0}"),FuncNameText);
    }
    return FText::Format(LOCTEXT("CallImmediateFunction", "CallImmediateFunction: {0}"), FuncNameText);
}
#endif // WITH_EDITOR

#undef LOCTEXT_NAMESPACE