#include "ARTSPlayerController.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"
#include "AshesOfWar/UI/Widgets/WResourceBarWidget.h"
#include "AshesOfWar/UI/HUD/MainHUD.h"
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

	// Get the Hud for the marquee selection drawing
	MainHUD = Cast<AMainHUD>(GetHUD());
}

void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind left and right click actions
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ARTSPlayerController::HandleLeftClick);
	InputComponent->BindAction("LeftClick", IE_Released, this, &ARTSPlayerController::HandleLeftClickRelease);
	InputComponent->BindAction("RightClick", IE_Pressed, this, &ARTSPlayerController::HandleRightClick);
}

void ARTSPlayerController::SetSelectedUnits(TArray<AUnit*>& NewUnits)
{
	for (AUnit* Unit : SelectedUnits)
	{
		if (Unit)
		{
			Unit->SetSelectedUnit(false); // Deselect previously selected units
		}
	}
	
	for (AUnit* Unit : NewUnits)
	{
		Unit->SetSelectedUnit(true);
		SelectedUnits.Add(Unit);
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
	TArray<AUnit*> CurSelectedUnits;
	if (AUnit* Unit = Cast<AUnit>(ClickedActor))
	{
		CurSelectedUnits.Add(Unit);
	}
	else
	{
		// Set beginning multiple selection to True
		bIsMousePressed = true;
		// Enable the tick to update the drawing of selection box
		PrimaryActorTick.bCanEverTick = true;
		// Record the start selection point
		float mouseX, mouseY;
		GetMousePosition(mouseX, mouseY);
		SelectionStartPosition = FVector2D(mouseX, mouseY);
	}
	SetSelectedUnits(CurSelectedUnits);
}

void ARTSPlayerController::HandleLeftClickRelease()
{
	// TODO Release the multiple selection box
	bIsMousePressed = false;
	PrimaryActorTick.bCanEverTick = false;
	MainHUD->HideSelectionRect();
}


void ARTSPlayerController::HandleRightClick()
{
	if (SelectedUnits.Num() <= 0)
		return;

	FHitResult Hit;
	const bool bHit = GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);

	if (!bHit || !Hit.bBlockingHit)
		return;

	const FVector TargetLocation = Hit.ImpactPoint;
	AActor* HitActor = Hit.GetActor();

	// If right-clicked on a resource node and selected unit is a miner
	for (AUnit* SelectedUnit : SelectedUnits)
	{
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

void ARTSPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// update the drawing of selection box if mouse is pressed
	if (bIsMousePressed)
	{
		float mouseX, mouseY;
		GetMousePosition(mouseX, mouseY);
		FVector2D SelectionSize = FVector2D(mouseX - SelectionStartPosition.X, mouseY - SelectionStartPosition.Y);
		MainHUD->ShowSelectionRect(
			SelectionStartPosition,
			SelectionSize);
	}
}
