#pragma once
#include "Tasks/StateTreeAITask.h"
#include "SetCurrentResourceNode.generated.h"
// Set the current ResourceNode of the Miner
USTRUCT()
struct FStateTreeSetCurrentResourceNodeTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<AActor> Actor = nullptr;

	UPROPERTY(EditAnywhere, Category = Parameter)
	TWeakObjectPtr<AActor> CurrentResource = nullptr;
};

/**
 * Task that sets the current resource node of a specified miner.
 */
USTRUCT(meta = (DisplayName = "Set Current ResourceNode", Category = "AI|Setter"))
struct FStateTreeSetCurrentResourceNodeTask : public FStateTreeAITaskBase
{
	GENERATED_BODY()
	using FInstanceDataType = struct FStateTreeSetCurrentResourceNodeTaskInstanceData;
		
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	GAMEPLAYSTATETREEMODULE_API virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	GAMEPLAYSTATETREEMODULE_API virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
	virtual FName GetIconName() const override
	{
		return FName("StateTreeEditorStyle|Node.SetCurrentResourceNode");
	}
	virtual FColor GetIconColor() const override
	{
		return UE::StateTree::Colors::Bronze;
	}
#endif // WITH_EDITOR
};