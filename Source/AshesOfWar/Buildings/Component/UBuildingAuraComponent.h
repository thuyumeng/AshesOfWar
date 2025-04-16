#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UBuildingAuraComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ASHESOFWAR_API UBuildingAuraComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBuildingAuraComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Vérifie les unités à proximité et applique l’effet
	void ApplyAuraToNearbyUnits();

private:
	UPROPERTY(EditAnywhere, Category = "Aura")
	float AuraRadius;

	UPROPERTY(EditAnywhere, Category = "Aura")
	bool bIsBuff; // true = buff, false = debuff

	UPROPERTY(EditAnywhere, Category = "Aura")
	TSubclassOf<class UGameplayEffect> AuraEffect;

	UPROPERTY()
	TArray<AActor*> AffectedUnits;
};