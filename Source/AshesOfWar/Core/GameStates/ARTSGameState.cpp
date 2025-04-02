// Fill out your copyright notice in the Description page of Project Settings.


#include "ARTSGameState.h"

AARTSGameState::AARTSGameState()
{
	
}

void AARTSGameState::BeginPlay()
{
	Super::BeginPlay();

	// Parcourt tous les joueurs présents dans la partie
	for (APlayerState* CurrentPlayer : PlayerArray)
	{
		if (!PlayerResources.Contains(CurrentPlayer))
		{
			// Crée une structure de ressources initiales
			FPlayerResourceData StartingResources;
			StartingResources.Aetherium = 500;
			StartingResources.Vitae = 0;
			StartingResources.Umbra = 0;

			// Associe le joueur à ses ressources dans la TMap
			PlayerResources.Add(CurrentPlayer, StartingResources);
		}
	}
}


void AARTSGameState::AddResource(APlayerState* Player, EResourceType ResourceType, int32 Amount)
{
	//* Vérifie si le Player est valide *//
	if (!Player) {return;}

	//* Vérifie si la TMap contient ce joueur *//
	if (!PlayerResources.Contains(Player)) return;

	//* Utilise un switch sur ResourceType pour ajouter la bonne ressource *//
	switch (ResourceType)
	{
	case EResourceType::Aetherium:
			PlayerResources[Player].Aetherium += Amount;
		case EResourceType::Vitae:
			PlayerResources[Player].Vitae += Amount;
	case EResourceType::Umbra:
		PlayerResources[Player].Umbra += Amount;
	}

	// case EResourceType::Aetherium: ajoute à PlayerResources[Player].Aetherium
	// etc.
}


bool AARTSGameState::SpendResource(APlayerState* Player, EResourceType ResourceType, int32 Amount)
{
	//* Vérifie si le Player est valide *//
	if (!Player) {return false;}

	//* Vérifie si la TMap contient ce joueur *//
	if (!PlayerResources.Contains(Player)) {return false;}

	//* Utilise un switch pour vérifier s’il a assez de la ressource demandée *//
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
	//* Vérifie si le Player est valide *//
	if (!Player) {return 0;}

	//* Vérifie si la TMap contient ce joueur *//
	if (!PlayerResources.Contains(Player)) {return 0;}

	//* Utilise un switch pour retourner la bonne ressource *//
	// case EResourceType::Vitae: return PlayerResources[Player].Vitae;
	switch (ResourceType)
	{
	case EResourceType::Aetherium:
		return  PlayerResources[Player].Aetherium;
		break;
	case EResourceType::Vitae:
		return PlayerResources[Player].Vitae;
		break;
	case EResourceType::Umbra:
		return PlayerResources[Player].Umbra;
		break;
	}

	return 0;
	//* Si le joueur n’est pas trouvé, retourne 0 *//
}


