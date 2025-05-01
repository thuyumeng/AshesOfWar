#pragma once
#include "Tasks/StateTreeAITask.h"
#include "CallImmediateFunctionTask.generated.h"

/**
 * Task that calls a immediate function on the specified actor.
 * Immediate function means it will finish immediately, not Delayed Task not Async Task.
 */

USTRUCT()
struct FStateTreeCallImmediateFunctionTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<AActor> Actor = nullptr;

	UPROPERTY(EditAnywhere, Category = Parameter)
	FName FunctionName;

	UPROPERTY(EditAnywhere, Category = Parameter)
	bool bFinishTaskWhenCalled = true;
};

USTRUCT(meta = (DisplayName = "Call Immediate Function From Actor", Category = "AI|Action"))
struct FStateTreeCallImmediateFunctionTask : public FStateTreeAITaskBase
{
	GENERATED_BODY()
	using FInstanceDataType = struct FStateTreeCallImmediateFunctionTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	GAMEPLAYSTATETREEMODULE_API virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	GAMEPLAYSTATETREEMODULE_API virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
	virtual FName GetIconName() const override
	{
		return FName("StateTreeEditorStyle|Node.CallImmediateFunction");
	}
	virtual FColor GetIconColor() const override
	{
		return UE::StateTree::Colors::Bronze;
	}
#endif // WITH_EDITOR
};
	
