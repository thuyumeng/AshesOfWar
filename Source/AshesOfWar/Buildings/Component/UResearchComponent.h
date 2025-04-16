#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UResearchComponent.generated.h"

USTRUCT(BlueprintType)
struct FResearchData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ResearchID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ResearchTime;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ASHESOFWAR_API UResearchComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UResearchComponent();

	UFUNCTION(BlueprintCallable, Category = "Research")
	void StartResearch(FName ResearchID);

	UFUNCTION(BlueprintCallable, Category = "Research")
	bool IsResearching() const;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = "Research")
	TArray<FResearchData> AvailableResearch;

	UPROPERTY()
	FName CurrentResearchID;

	UPROPERTY()
	float CurrentResearchTimeRemaining;

	UPROPERTY()
	float TotalResearchTime;

	UPROPERTY()
	bool bIsResearching;
};