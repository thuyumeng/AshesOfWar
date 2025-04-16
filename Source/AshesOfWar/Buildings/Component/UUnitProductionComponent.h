#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UUnitProductionComponent.generated.h"

class AUnit;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ASHESOFWAR_API UUnitProductionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUnitProductionComponent();

	UFUNCTION(BlueprintCallable, Category = "Production")
	void StartProduction(TSubclassOf<AUnit> UnitClass);

	UFUNCTION(BlueprintCallable, Category = "Production")
	void CancelProduction();

	UFUNCTION(BlueprintPure, Category = "Production")
	bool IsProducing() const;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TSubclassOf<AUnit> CurrentUnitClass;

	UPROPERTY()
	float TimeRemaining;

	UPROPERTY()
	float TotalProductionTime;

	UPROPERTY()
	bool bIsProducing;
};
