// Fill out your copyright notice in the Description page of Project Settings.

#include "ARTSGameState.h"

AARTSGameState::AARTSGameState()
{
	// Constructor logic (if needed)
}

void AARTSGameState::BeginPlay()
{
	Super::BeginPlay();

	// Loop through all players and assign them starting resources
	for (APlayerState* CurrentPlayer : PlayerArray)
	{
		if (!PlayerResources.Contains(CurrentPlayer))
		{
			FPlayerResourceData StartingResources;
			StartingResources.Aetherium = 500;
			StartingResources.Vitae = 0;
			StartingResources.Umbra = 0;

			PlayerResources.Add(CurrentPlayer, StartingResources);
		}
	}
}

void AARTSGameState::AddResource(APlayerState* Player, EResourceType ResourceType, int32 Amount)
{
	if (!Player || !PlayerResources.Contains(Player)) return;

	// Add the amount to the appropriate resource field
	switch (ResourceType)
	{
	case EResourceType::Aetherium:
		PlayerResources[Player].Aetherium += Amount;
		break;
	case EResourceType::Vitae:
		PlayerResources[Player].Vitae += Amount;
		break;
	case EResourceType::Umbra:
		PlayerResources[Player].Umbra += Amount;
		break;
	default:
		break;
	}
}

bool AARTSGameState::SpendResource(APlayerState* Player, EResourceType ResourceType, int32 Amount)
{
	if (!Player || !PlayerResources.Contains(Player)) return false;

	// Subtract the amount only if the player has enough of that resource
	switch (ResourceType)
	{
	case EResourceType::Aetherium:
		if (PlayerResources[Player].Aetherium >= Amount)
		{
			PlayerResources[Player].Aetherium -= Amount;
			return true;
		}
		break;

	case EResourceType::Vitae:
		if (PlayerResources[Player].Vitae >= Amount)
		{
			PlayerResources[Player].Vitae -= Amount;
			return true;
		}
		break;

	case EResourceType::Umbra:
		if (PlayerResources[Player].Umbra >= Amount)
		{
			PlayerResources[Player].Umbra -= Amount;
			return true;
		}
		break;
	}

	return false;
}

int32 AARTSGameState::GetResourceAmount(APlayerState* Player, EResourceType ResourceType) const
{
	if (!Player || !PlayerResources.Contains(Player)) return 0;

	// Return the value of the requested resource
	switch (ResourceType)
	{
	case EResourceType::Aetherium:
		return PlayerResources[Player].Aetherium;
	case EResourceType::Vitae:
		return PlayerResources[Player].Vitae;
	case EResourceType::Umbra:
		return PlayerResources[Player].Umbra;
	default:
		return 0;
	}
}
