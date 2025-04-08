#include "ARTSPlayerController.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"

ARTSPlayerController::ARTSPlayerController()
{
	bEnableClickEvents = true;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ARTSPlayerController::HandleLeftClick);
	InputComponent->BindAction("RightClick", IE_Pressed, this, &ARTSPlayerController::HandleRightClick);
}

void ARTSPlayerController::SetSelectedUnit(AUnit* NewUnit)
{
	SelectedUnit = NewUnit;

	if (SelectedUnit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unité sélectionnée : %s"), *SelectedUnit->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Aucune unité sélectionnée"));
	}
}

void ARTSPlayerController::HandleLeftClick()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleLeftClick appelé"));

	FHitResult Hit;
	bool bHit = GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);

	if (!bHit || !Hit.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Aucun Hit détecté sous curseur."));
		return;
	}

	AActor* ClickedActor = Hit.GetActor();
	UPrimitiveComponent* ClickedComponent = Hit.Component.Get();

	UE_LOG(LogTemp, Warning, TEXT("Hit détecté sur : %s | Composant : %s"),
		ClickedActor ? *ClickedActor->GetName() : TEXT("Aucun"),
		ClickedComponent ? *ClickedComponent->GetName() : TEXT("Aucun"));

	if (AUnit* Unit = Cast<AUnit>(ClickedActor))
	{
		SetSelectedUnit(Unit);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Aucune unité valide sélectionnée."));
	}
}

void ARTSPlayerController::HandleRightClick()
{
	if (!SelectedUnit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Aucune unité sélectionnée, clic droit ignoré."));
		return;
	}

	FHitResult Hit;
	bool bHit = GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);

	if (!bHit || !Hit.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Clic droit sans Hit valide"));
		return;
	}

	const FVector TargetLocation = Hit.ImpactPoint;
	AActor* HitActor = Hit.GetActor();

	UE_LOG(LogTemp, Warning, TEXT("Clic droit - Hit sur : %s à %s"),
		HitActor ? *HitActor->GetName() : TEXT("Aucun"),
		*TargetLocation.ToString());

	// Si clic sur node de ressource
	if (AAResourceNode* Resource = Cast<AAResourceNode>(HitActor))
	{
		if (AMiner* Miner = Cast<AMiner>(SelectedUnit))
		{
			Miner->SetCurrentResourceNode(Resource);
			Miner->MoveToLocation(TargetLocation);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("L'unité sélectionnée ne peut pas miner."));
		}
	}
	else
	{
		SelectedUnit->MoveToLocation(TargetLocation);
	}
}
