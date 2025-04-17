#include "UResearchComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "AshesOfWar/Core/GameStates/AAshesOfWarGameState.h"

UResearchComponent::UResearchComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize defaults
	bIsResearching = false;
	CurrentResearchTimeRemaining = 0.0f;
	TotalResearchTime = 0.0f;
}

void UResearchComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UResearchComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsResearching)
	{
		return;
	}

	// Update research progress
	CurrentResearchTimeRemaining -= DeltaTime;

	// If research is completed
	if (CurrentResearchTimeRemaining <= 0.0f)
	{
		bIsResearching = false;

		UE_LOG(LogTemp, Log, TEXT("Research completed: %s"), *CurrentResearchID.ToString());

		// TODO: Implement logic here to apply research effects, unlock tech, or notify the GameState
	}
}

void UResearchComponent::StartResearch(FName ResearchID)
{
	// Prevent starting a new research if one is already active
	if (bIsResearching)
	{
		UE_LOG(LogTemp, Warning, TEXT("StartResearch: Already researching another project."));
		return;
	}

	// Search for the requested research in the available list
	for (const FResearchData& Entry : AvailableResearch)
	{
		if (Entry.ResearchID == ResearchID)
		{
			CurrentResearchID = ResearchID;
			TotalResearchTime = Entry.ResearchTime;
			CurrentResearchTimeRemaining = TotalResearchTime;
			bIsResearching = true;

			UE_LOG(LogTemp, Log, TEXT("Research started: %s (%.2fs)"), *ResearchID.ToString(), TotalResearchTime);
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("StartResearch: Research ID '%s' not found in the available list."), *ResearchID.ToString());
}

bool UResearchComponent::IsResearching() const
{
	return bIsResearching;
}
