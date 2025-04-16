#include "UBuildingManagerSubsystem.h"
#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"
#include "AshesOfWar/Buildings/Base/ABuildingGhostActor.h"
#include "AshesOfWar/Core/GameStates/ARTSGameState.h"
#include "AshesOfWar/Resources/Management/UResourceLibrary.h"
#include "AshesOfWar/Resources/ResourcesTypes/FPlayerResourceData.h"
#include "AshesOfWar/Resources/ResourcesTypes/EResourceType.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"

void UBuildingManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// ⚠️ Tu dois définir GhostActorClass depuis le GameInstance ou via Blueprint
}

bool UBuildingManagerSubsystem::TryPlaceBuildingAtLocation(const FVector& Location, TSubclassOf<ABaseBuilding> BuildingClass)
{
	if (!BuildingClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("TryPlaceBuildingAtLocation - Classe de bâtiment invalide."));
		return false;
	}

	UWorld* World = GetWorld();
	if (!World) return false;

	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	if (!PC) return false;

	APlayerState* PlayerState = PC->GetPlayerState<APlayerState>();
	if (!PlayerState) return false;

	const ABaseBuilding* BuildingCDO = BuildingClass->GetDefaultObject<ABaseBuilding>();
	if (!BuildingCDO) return false;

	const FBuildingInfo& Info = BuildingCDO->BuildingData;

	// Convertir TMap<EResourceType, int32> → FPlayerResourceData pour le CanAfford()
	FPlayerResourceData BuildingCost;
	for (const TPair<EResourceType, int32>& Pair : Info.ResourceCost)
	{
		switch (Pair.Key)
		{
		case EResourceType::Aetherium:
			BuildingCost.Aetherium = Pair.Value;
			break;
		case EResourceType::Vitae:
			BuildingCost.Vitae = Pair.Value;
			break;
		case EResourceType::Umbra:
			BuildingCost.Umbra = Pair.Value;
			break;
		default:
			break;
		}
	}

	if (!UResourceLibrary::CanAfford(PlayerState, BuildingCost))
	{
		UE_LOG(LogTemp, Warning, TEXT("Le joueur n’a pas les ressources nécessaires."));
		return false;
	}

	// Raycast au sol
	FHitResult Hit;
	PC->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);
	if (!Hit.bBlockingHit) return false;

	FVector HitLocation = Hit.ImpactPoint;
	bool bPlacementValide = false;

	// 1. Vérifier la pente
	const float SurfaceZ = Hit.ImpactNormal.Z;
	const bool bSurfacePlat = SurfaceZ >= 0.9f;

	// 2. Vérifier qu’aucun obstacle
	FVector BoxExtent(0.f);
	if (const UBoxComponent* Box = BuildingCDO->FindComponentByClass<UBoxComponent>())
	{
		BoxExtent = Box->GetScaledBoxExtent();
		FVector AdjustedLocation = HitLocation + FVector(0.f, 0.f, BoxExtent.Z);

		FCollisionShape Shape = FCollisionShape::MakeBox(BoxExtent);
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(CurrentGhost);

		bool bObstacle = World->SweepTestByChannel(
			AdjustedLocation, AdjustedLocation, FQuat::Identity,
			ECC_WorldStatic, Shape, Params);

		bPlacementValide = bSurfacePlat && !bObstacle;
	}

	// Créer ou mettre à jour le GhostActor
	if (!CurrentGhost && GhostActorClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		CurrentGhost = World->SpawnActor<ABuildingGhostActor>(GhostActorClass, HitLocation, FRotator::ZeroRotator, SpawnParams);

		if (CurrentGhost && BuildingCDO)
		{
			if (UStaticMeshComponent* Mesh = BuildingCDO->FindComponentByClass<UStaticMeshComponent>())
			{
				CurrentGhost->SetPreviewMesh(Mesh->GetStaticMesh());
			}
		}
	}

	if (CurrentGhost)
	{
		CurrentGhost->SetActorLocation(HitLocation);
		CurrentGhost->SetValidPlacement(bPlacementValide);

		if (PC->WasInputKeyJustPressed(EKeys::LeftMouseButton) && bPlacementValide)
		{
			// Déduction des ressources une par une
			AARTSGameState* GameState = Cast<AARTSGameState>(UGameplayStatics::GetGameState(World));
			if (!GameState) return false;

			for (const TPair<EResourceType, int32>& Pair : Info.ResourceCost)
			{
				GameState->SpendResource(PlayerState, Pair.Key, Pair.Value);
			}

			// Spawn du vrai bâtiment
			FActorSpawnParameters FinalParams;
			FinalParams.Owner = PC;
			FinalParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			ABaseBuilding* NewBuilding = World->SpawnActor<ABaseBuilding>(BuildingClass, HitLocation, FRotator::ZeroRotator, FinalParams);
			if (NewBuilding)
			{
				NewBuilding->OwningPlayer = PlayerState;
			}

			ClearGhost();
			return true;
		}
	}

	return false;
}

void UBuildingManagerSubsystem::ClearGhost()
{
	if (CurrentGhost)
	{
		CurrentGhost->Destroy();
		CurrentGhost = nullptr;
	}
}

ABuildingGhostActor* UBuildingManagerSubsystem::GetCurrentGhost() const
{
	return CurrentGhost;
}
