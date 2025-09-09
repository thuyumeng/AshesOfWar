#pragma once
#include "Tasks/StateTreeAITask.h"
#include "GetCurrentResourceNode.generated.h"


USTRUCT()
struct FStateTreeGetCurrentResourceTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<AActor> Actor = nullptr;
	
	// The output variable to store the found actor
	UPROPERTY(EditAnywhere, Category = Output)
	TObjectPtr<AActor> ResourceNode;
};

/**
 * Task that gets the miner’s current resource node.
 * The result is stored in the provided output variable.
 */
USTRUCT(meta = (DisplayName = "Get Current Resource Node", Category = "AI|Getter"))
struct FStateTreeGetCurrentResourceTask : public FStateTreeAITaskBase
{
	GENERATED_BODY()
	using FInstanceDataType = FStateTreeGetCurrentResourceTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
	virtual FName GetIconName() const override
	{
		return FName("StateTreeEditorStyle|Node.GetCurrentResourceNode");
	}
	virtual FColor GetIconColor() const override
	{
		return UE::StateTree::Colors::Bronze;
	}
#endif // WITH_EDITOR
};
