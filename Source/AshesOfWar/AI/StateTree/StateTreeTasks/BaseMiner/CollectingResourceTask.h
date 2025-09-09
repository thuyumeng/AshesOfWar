#pragma once
#include "Tasks/StateTreeAITask.h"
#include "CollectingResourceTask.generated.h"

class AMiner;

USTRUCT()
struct FStateTreeCollectingResourceTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<AActor> Actor = nullptr;
};

/**
 * Task that collects resources from a specified miner.
 */
USTRUCT(meta = (DisplayName = "Collecting Resource", Category = "AI|Action"))
struct FStateTreeCollectingTask : public FStateTreeAITaskBase
{
	GENERATED_BODY()
	using FInstanceDataType = FStateTreeCollectingResourceTaskInstanceData;
		
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
	virtual FName GetIconName() const override
	{
		return FName("StateTreeEditorStyle|Node.CollectingResource");
	}
	virtual FColor GetIconColor() const override
	{
		return UE::StateTree::Colors::Bronze;
	}
#endif // WITH_EDITOR
};