#pragma once
#include "Tasks/StateTreeAITask.h"
#include "GetCurrentDepositBase.generated.h"


USTRUCT()
struct FStateTreeGetCurrentDepositBaseTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<AActor> Actor = nullptr;
	
	// The output variable to store the found actor
	UPROPERTY(EditAnywhere, Category = Output)
	TObjectPtr<AActor> DepositBase;
};

/**
 * Task that get the miner's current deposit base.
 * The result is stored in the provided output variable.
 */
USTRUCT(meta = (DisplayName = "Get Current Deposit Base", Category = "AI|Getter"))
struct FStateTreeGetCurrentDepositBaseTask : public FStateTreeAITaskBase
{
	GENERATED_BODY()
	using FInstanceDataType = FStateTreeGetCurrentDepositBaseTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	GAMEPLAYSTATETREEMODULE_API virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	GAMEPLAYSTATETREEMODULE_API virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
	virtual FName GetIconName() const override
	{
		return FName("StateTreeEditorStyle|Node.GetCurrentDepositBase");
	}
	virtual FColor GetIconColor() const override
	{
		return UE::StateTree::Colors::Bronze;
	}
#endif // WITH_EDITOR
};
