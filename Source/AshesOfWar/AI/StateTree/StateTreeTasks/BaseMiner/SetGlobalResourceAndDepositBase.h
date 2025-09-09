#pragma once
#include "Tasks/StateTreeAITask.h"
#include "StateTreePropertyRef.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"
#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"
#include "SetGlobalResourceAndDepositBase.generated.h"
// Set the global parameters (ResourceNode and DepositBase) of the Miner


USTRUCT()
struct FStateTreeSetGlobalResourceAndDepositBaseTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<AActor> Actor = nullptr;
	
	UPROPERTY(EditAnywhere, Category = Parameter)
	TStateTreePropertyRef<bool> BIsResourceSet;
	
	UPROPERTY(EditAnywhere, Category = Parameter)
	TStateTreePropertyRef<bool> BIsDepositBase;
};

/**
 * Task that sets the current resource node of a specified miner.
 */
USTRUCT(meta = (DisplayName = "Set Global Resource And DepositBase", Category = "AI|Setter"))
struct FStateTreeSetGlobalResourceAndDepositBaseTask : public FStateTreeAITaskBase
{
	GENERATED_BODY()
	using FInstanceDataType = FStateTreeSetGlobalResourceAndDepositBaseTaskInstanceData;
		
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
	virtual FName GetIconName() const override
	{
		return FName("StateTreeEditorStyle|Node.SetGlobalResourceAndDepositBase");
	}
	virtual FColor GetIconColor() const override
	{
		return UE::StateTree::Colors::Bronze;
	}
#endif // WITH_EDITOR
};