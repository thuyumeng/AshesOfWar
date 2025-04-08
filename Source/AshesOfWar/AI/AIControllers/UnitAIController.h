// AI Controller class for RTS units in Ashes of War

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "UnitAIController.generated.h"

class UUnitStateTreeAIComponent;

/**
 * AUnitAIController
 * Custom AIController class managing RTS unit behavior via StateTree.
 */
UCLASS()
class ASHESOFWAR_API AUnitAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Constructor: Initializes this AI Controller with a StateTree component
	explicit AUnitAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game begins or this controller is spawned
	virtual void BeginPlay() override;

public:
	// Getter sécurisé du StateTree AI Component
	UFUNCTION(BlueprintCallable, Category = "AI")
	UUnitStateTreeAIComponent* GetUnitStateTreeAIComponent() const;

private:
	// Instance du composant AI StateTree (non modifiable dans l'éditeur)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUnitStateTreeAIComponent> UnitStateTreeAIComponent;
};
