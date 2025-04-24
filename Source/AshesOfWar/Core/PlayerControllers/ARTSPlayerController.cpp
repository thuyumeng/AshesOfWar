#include "ARTSPlayerController.h"
#include "AshesOfWar/Units/Base/Unit.h"
#include "AshesOfWar/Units/Base/Miner/Miner.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"
#include "AshesOfWar/UI/Widgets/WResourceBarWidget.h"
#include "AshesOfWar/UI/HUD/MainHUD.h"
#include "AshesOfWar/Core/GameStates/ARTSGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerState.h"

// --- Constructor ---
ARTSPlayerController::ARTSPlayerController()
{
	bEnableClickEvents = true;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	static ConstructorHelpers::FClassFinder<UWResourceBarWidget> ResourceBarBPClass(TEXT("/Game/Blueprints/UI/WBP_ResourceBar"));
	if (ResourceBarBPClass.Succeeded())
	{
		ResourceBarClass = ResourceBarBPClass.Class;
	}
}

// --- BeginPlay ---
void ARTSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() && ResourceBarClass)
	{
		ResourceBarInstance = CreateWidget<UWResourceBarWidget>(this, ResourceBarClass);
		if (ResourceBarInstance)
		{
			ResourceBarInstance->AddToViewport();

			GetWorldTimerManager().SetTimer(ResourceUpdateTimerHandle, this, &ARTSPlayerController::UpdateResourceUI, 1.0f, true);
		}
	}

	MainHUD = Cast<AMainHUD>(GetHUD());
}

// --- Input Setup ---
void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ARTSPlayerController::HandleLeftClick);
	InputComponent->BindAction("LeftClick", IE_Released, this, &ARTSPlayerController::HandleLeftClickRelease);
	InputComponent->BindAction("RightClick", IE_Pressed, this, &ARTSPlayerController::HandleRightClick);
}

// --- Selection ---
void ARTSPlayerController::SetSelectedUnits(TArray<AUnit*>& NewUnits)
{
	for (AUnit* Unit : SelectedUnits)
	{
		if (Unit)
		{
			Unit->SetSelectedUnit(false);
		}
	}
	SelectedUnits.Empty();

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
	TArray<AUnit*> CurSelectedUnits;

	if (AUnit* Unit = Cast<AUnit>(ClickedActor))
	{
		CurSelectedUnits.Add(Unit);
	}
	else
	{
		bIsMousePressed = true;
		PrimaryActorTick.bCanEverTick = true;

		float mouseX, mouseY;
		GetMousePosition(mouseX, mouseY);
		SelectionStartPosition = FVector2D(mouseX, mouseY);
	}

	SetSelectedUnits(CurSelectedUnits);
}

void ARTSPlayerController::HandleLeftClickRelease()
{
	bIsMousePressed = false;
	PrimaryActorTick.bCanEverTick = false;

	if (MainHUD)
	{
		MainHUD->HideSelectionRect();
	}
}

void ARTSPlayerController::HandleRightClick()
{
	if (SelectedUnits.Num() <= 0) return;

	FHitResult Hit;
	const bool bHit = GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);
	if (!bHit || !Hit.bBlockingHit) return;

	const FVector TargetLocation = Hit.ImpactPoint;
	AActor* HitActor = Hit.GetActor();

	for (AUnit* SelectedUnit : SelectedUnits)
	{
		if (AAResourceNode* Resource = Cast<AAResourceNode>(HitActor))
		{
			if (AMiner* Miner = Cast<AMiner>(SelectedUnit))
			{
				Miner->SetCurrentResourceNode(Resource);
				Miner->MoveToLocation(TargetLocation);
				Miner->MineResource();

				UE_LOG(LogTemp, Log, TEXT("[RTS] Miner %s assigned to resource node %s"), *Miner->GetName(), *Resource->GetName());
			}
		}
		else
		{
			SelectedUnit->MoveToLocation(TargetLocation);
		}
	}
}

// --- Resource UI ---
void ARTSPlayerController::UpdateResourceUI()
{
	AARTSGameState* GameState = GetWorld() ? GetWorld()->GetGameState<AARTSGameState>() : nullptr;
	if (!GameState || !ResourceBarInstance) return;

	APlayerState* MyPlayerState = GetPlayerState<APlayerState>();
	if (!MyPlayerState) return;

	const int32 Aetherium = GameState->GetResourceAmount(MyPlayerState, EResourceType::Aetherium);
	const int32 Vitae = GameState->GetResourceAmount(MyPlayerState, EResourceType::Vitae);
	const int32 Umbra = GameState->GetResourceAmount(MyPlayerState, EResourceType::Umbra);

	ResourceBarInstance->UpdateResources(Aetherium, Vitae, Umbra);

	// Keep this for active debug – remove or demote in final release
	UE_LOG(LogTemp, Log, TEXT("[Resources] Aetherium: %d | Vitae: %d | Umbra: %d"), Aetherium, Vitae, Umbra);
}

// --- Tick for selection marquee ---
void ARTSPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsMousePressed && MainHUD)
	{
		float mouseX, mouseY;
		GetMousePosition(mouseX, mouseY);
		FVector2D SelectionSize = FVector2D(mouseX - SelectionStartPosition.X, mouseY - SelectionStartPosition.Y);
		MainHUD->ShowSelectionRect(SelectionStartPosition, SelectionSize);
	}
}
