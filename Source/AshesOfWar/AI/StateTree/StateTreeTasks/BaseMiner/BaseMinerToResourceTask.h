#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITypes.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "BaseMinerToResourceTask.generated.h"

class AUnitAIController;

UCLASS()
class ASHESOFWAR_API UBaseMinerToResourceTask : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	UBaseMinerToResourceTask();

protected:
	// Move completed callback
	UFUNCTION(BlueprintCallable)
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

	// Move to current mining or deposit target
	void MoveToCurrentTarget();

	// Fonction appelée à l'entrée du State
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

private:
	// Le contrôleur du mineur
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Context", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AUnitAIController> AIController;
};
