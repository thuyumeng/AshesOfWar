#pragma once
#include "Tasks/StateTreeAITask.h"
#include "SetCurrentDepositBase.generated.h"
// Set the current ResourceNode of the Miner
USTRUCT()


struct FStateTreeSetCurrentDepositBaseTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<AActor> Actor = nullptr;

	UPROPERTY(EditAnywhere, Category = Parameter)
	TWeakObjectPtr<AActor> DepositBase = nullptr;
};

/**
 * Task that sets the current resource node of a specified miner.
 */
USTRUCT(meta = (DisplayName = "Set Current DepositBase", Category = "AI|Setter"))
struct FStateTreeSetCurrentDepositBaseTask : public FStateTreeAITaskBase
{
	GENERATED_BODY()
	using FInstanceDataType = FStateTreeSetCurrentDepositBaseTaskInstanceData;
		
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
	virtual FName GetIconName() const override
	{
		return FName("StateTreeEditorStyle|Node.SetCurrentDepositBase");
	}
	virtual FColor GetIconColor() const override
	{
		return UE::StateTree::Colors::Bronze;
	}
#endif // WITH_EDITOR
};