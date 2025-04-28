#pragma once
#include "Tasks/StateTreeAITask.h"
#include "FFindNearestActorTask.generated.h"

USTRUCT()
struct FStateTreeFindNearestActorTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<AActor> Actor = nullptr;

	// The max search radius for finding the nearest actor
	UPROPERTY(EditAnywhere, Category = Parameter)
	float SearchRadius = 1000000.f;

	// The class of the actor to find
	UPROPERTY(EditAnywhere, Category = Parameter)
	TSubclassOf<AActor> TargetActorClass;

	//// The output variable to store the found actor
	UPROPERTY(EditAnywhere, Category = Output)
	TObjectPtr<AActor> FoundActor;
};

/**
 * Task that finds the nearest actor of a specified class within a given radius.
 * The result is stored in the provided output variable.
 */
USTRUCT(meta = (DisplayName = "Find Nearest Actor", Category = "AI|Action"))
struct FStateTreeFindNearestActorTask : public FStateTreeAITaskBase
{
	GENERATED_BODY()
	using FInstanceDataType = FStateTreeFindNearestActorTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	GAMEPLAYSTATETREEMODULE_API virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	GAMEPLAYSTATETREEMODULE_API virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

	// utility function to get all actors of a specific class within a radius
	static void GetNearestActorOfClass(const UWorld* World, const TSubclassOf<AActor>& ActorClass, TObjectPtr<AActor>& OutActor, float Radius, const TObjectPtr<AActor>& ContextActor);
#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
	virtual FName GetIconName() const override
	{
		return FName("StateTreeEditorStyle|Node.FindNearestActor");
	}
	virtual FColor GetIconColor() const override
	{
		return UE::StateTree::Colors::Bronze;
	}
#endif // WITH_EDITOR
};
