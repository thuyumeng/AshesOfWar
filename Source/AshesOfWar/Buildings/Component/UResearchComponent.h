#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UResearchComponent.generated.h"

/**
 * FResearchData
 * 
 * Structure containing the necessary data for a research entry.
 */
USTRUCT(BlueprintType)
struct FResearchData
{
	GENERATED_BODY()

	/** Unique ID for identifying the research. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ResearchID;

	/** Description of the research for UI or gameplay usage. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	/** Total time required to complete the research (in seconds). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ResearchTime;
};

/**
 * UResearchComponent
 * 
 * Component that manages research progression for buildings or tech structures.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASHESOFWAR_API UResearchComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Constructor
	UResearchComponent();

	/**
	 * Starts a research project given a valid research ID.
	 */
	UFUNCTION(BlueprintCallable, Category = "Research")
	void StartResearch(FName ResearchID);

	/**
	 * Returns whether a research is currently in progress.
	 */
	UFUNCTION(BlueprintCallable, Category = "Research")
	bool IsResearching() const;

protected:
	/** Called when the game starts. */
	virtual void BeginPlay() override;

	/** Called every frame to update research progress if active. */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/** List of available research options for this building/component. */
	UPROPERTY(EditAnywhere, Category = "Research")
	TArray<FResearchData> AvailableResearch;

	/** ID of the currently researched project. */
	UPROPERTY()
	FName CurrentResearchID;

	/** Remaining time left to complete the active research. */
	UPROPERTY()
	float CurrentResearchTimeRemaining;

	/** Total time originally required for the active research. */
	UPROPERTY()
	float TotalResearchTime;

	/** Whether a research is currently active. */
	UPROPERTY()
	bool bIsResearching;
};
