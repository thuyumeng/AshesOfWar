#include "UResearchComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "AshesOfWar/Core/GameStates/AAshesOfWarGameState.h"

UResearchComponent::UResearchComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsResearching = false;
	CurrentResearchTimeRemaining = 0.f;
	TotalResearchTime = 0.f;
}

void UResearchComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UResearchComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsResearching) return;

	CurrentResearchTimeRemaining -= DeltaTime;

	if (CurrentResearchTimeRemaining <= 0.f)
	{
		bIsResearching = false;

		UE_LOG(LogTemp, Log, TEXT("Recherche complétée : %s"), *CurrentResearchID.ToString());

		// Tu peux ici appliquer les effets débloqués, ajouter un tag ou notifier le GameState
	}
}

void UResearchComponent::StartResearch(FName ResearchID)
{
	if (bIsResearching) return;

	for (const FResearchData& Entry : AvailableResearch)
	{
		if (Entry.ResearchID == ResearchID)
		{
			CurrentResearchID = ResearchID;
			TotalResearchTime = Entry.ResearchTime;
			CurrentResearchTimeRemaining = TotalResearchTime;
			bIsResearching = true;

			UE_LOG(LogTemp, Log, TEXT("Début recherche : %s (%.2fs)"), *ResearchID.ToString(), TotalResearchTime);
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("StartResearch : ID '%s' introuvable dans la liste."), *ResearchID.ToString());
}

bool UResearchComponent::IsResearching() const
{
	return bIsResearching;
}
