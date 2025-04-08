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

	// Bind left and right click to their respective handlers
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ARTSPlayerController::HandleLeftClick);
	InputComponent->BindAction("RightClick", IE_Pressed, this, &ARTSPlayerController::HandleRightClick);
}

void ARTSPlayerController::SetSelectedUnit(AUnit* NewUnit)
{
	SelectedUnit = NewUnit;

	// Important log to trace selection
	if (SelectedUnit)
	{
		UE_LOG(LogTemp, Log, TEXT("Selected unit: %s"), *SelectedUnit->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No unit selected."));
	}
}

void ARTSPlayerController::HandleLeftClick()
{
	FHitResult Hit;
	bool bHit = GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);

	if (!bHit || !Hit.bBlockingHit)
		return;

	AActor* ClickedActor = Hit.GetActor();

	// Try selecting the unit if the clicked actor is valid
	if (AUnit* Unit = Cast<AUnit>(ClickedActor))
	{
		SetSelectedUnit(Unit);
	}
}

void ARTSPlayerController::HandleRightClick()
{
	if (!SelectedUnit)
		return;

	FHitResult Hit;
	bool bHit = GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);

	if (!bHit || !Hit.bBlockingHit)
		return;

	const FVector TargetLocation = Hit.ImpactPoint;
	AActor* HitActor = Hit.GetActor();

	// If clicked on a resource node, try assigning a miner
	if (AAResourceNode* Resource = Cast<AAResourceNode>(HitActor))
	{
		if (AMiner* Miner = Cast<AMiner>(SelectedUnit))
		{
			Miner->SetCurrentResourceNode(Resource);
			Miner->MoveToLocation(TargetLocation);
		}
	}
	else
	{
		// Regular move order
		SelectedUnit->MoveToLocation(TargetLocation);
	}
}
