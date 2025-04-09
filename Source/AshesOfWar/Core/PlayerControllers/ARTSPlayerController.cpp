#include "ARTSPlayerController.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"
#include "AshesOfWar/UI/Widgets/WResourceBarWidget.h"
#include "AshesOfWar/Core/GameStates/ARTSGameState.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"

ARTSPlayerController::ARTSPlayerController()
{
	bEnableClickEvents = true;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	// Load the resource bar widget blueprint class
	static ConstructorHelpers::FClassFinder<UWResourceBarWidget> ResourceBarBPClass(TEXT("/Game/Blueprints/UI/WBP_ResourceBar"));
	if (ResourceBarBPClass.Succeeded())
	{
		ResourceBarClass = ResourceBarBPClass.Class;
	}
}

void ARTSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Only spawn the resource bar widget for the local player
	if (IsLocalController() && ResourceBarClass)
	{
		ResourceBarInstance = CreateWidget<UWResourceBarWidget>(this, ResourceBarClass);
		if (ResourceBarInstance)
		{
			ResourceBarInstance->AddToViewport();

			// Set up a timer to refresh resource values every second
			GetWorldTimerManager().SetTimer(ResourceUpdateTimerHandle, this, &ARTSPlayerController::UpdateResourceUI, 1.0f, true);
		}
	}
}

void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind left and right click actions
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ARTSPlayerController::HandleLeftClick);
	InputComponent->BindAction("RightClick", IE_Pressed, this, &ARTSPlayerController::HandleRightClick);
}

void ARTSPlayerController::SetSelectedUnit(AUnit* NewUnit)
{
	SelectedUnit = NewUnit;

	// Log for debugging
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
	const bool bHit = GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);

	if (!bHit || !Hit.bBlockingHit)
		return;

	AActor* ClickedActor = Hit.GetActor();

	// If a unit was clicked, select it
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
	const bool bHit = GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);

	if (!bHit || !Hit.bBlockingHit)
		return;

	const FVector TargetLocation = Hit.ImpactPoint;
	AActor* HitActor = Hit.GetActor();

	// If right-clicked on a resource node and selected unit is a miner
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
		// Otherwise, move the selected unit to the target location
		SelectedUnit->MoveToLocation(TargetLocation);
	}
}

void ARTSPlayerController::UpdateResourceUI()
{
	if (!ResourceBarInstance) return;

	APlayerState* PS = PlayerState;
	AARTSGameState* GS = Cast<AARTSGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (!GS || !PS) return;

	// Get current player resources
	const int32 Aetherium = GS->GetResourceAmount(PS, EResourceType::Aetherium);
	const int32 Vitae     = GS->GetResourceAmount(PS, EResourceType::Vitae);
	const int32 Umbra     = GS->GetResourceAmount(PS, EResourceType::Umbra);

	// Update the UI with latest values
	ResourceBarInstance->UpdateResources(Aetherium, Vitae, Umbra);
}
