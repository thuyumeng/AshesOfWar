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

	// ✅ ICI : Charger le widget UI au moment de l'initialisation de la classe
	static ConstructorHelpers::FClassFinder<UWResourceBarWidget> ResourceBarBPClass(TEXT("/Game/Blueprints/UI/WBP_ResourceBar"));
	if (ResourceBarBPClass.Succeeded())
	{
		ResourceBarClass = ResourceBarBPClass.Class;
	}
}


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

	if (AUnit* Unit = Cast<AUnit>(ClickedActor))
	{
		SetSelectedUnit(Unit);
	}
}

void ARTSPlayerController::HandleRightClick()
{
	if (!SelectedUnit) return;

	FHitResult Hit;
	bool bHit = GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);

	if (!bHit || !Hit.bBlockingHit)
		return;

	const FVector TargetLocation = Hit.ImpactPoint;
	AActor* HitActor = Hit.GetActor();

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
		SelectedUnit->MoveToLocation(TargetLocation);
	}
}

void ARTSPlayerController::UpdateResourceUI()
{
	if (!ResourceBarInstance) return;

	APlayerState* PS = PlayerState;;
	AARTSGameState* GS = Cast<AARTSGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (!GS || !PS) return;

	int32 Aetherium = GS->GetResourceAmount(PS, EResourceType::Aetherium);
	int32 Vitae = GS->GetResourceAmount(PS, EResourceType::Vitae);
	int32 Umbra = GS->GetResourceAmount(PS, EResourceType::Umbra);

	ResourceBarInstance->UpdateResources(Aetherium, Vitae, Umbra);
}
