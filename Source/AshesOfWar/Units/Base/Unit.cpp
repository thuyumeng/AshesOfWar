#include "Unit.h"

// GAS and AI includes
#include "AshesOfWar/Ability/Base/AOWAbilitySystemComponent.h"
#include "AshesOfWar/Ability/Base/Attributes/AOWAttributeSet.h"
#include "AshesOfWar/Ability/Base/Attributes/HealthAttributeSet.h"
#include "AshesOfWar/Ability/Base/Attributes/MoveAttributeSet.h"
#include "AshesOfWar/AI/AIControllers/UnitAIController.h"
#include "Components/CapsuleComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/DecalComponent.h"

// Constructor
AUnit::AUnit()
{
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAOWAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	InitializeDecal();
}

// Custom hook (BlueprintNativeEvent)
void AUnit::OnBeginPlay_Implementation()
{
	// Optional: add a debug log or override in blueprint
}

// Called at unit spawn
void AUnit::BeginPlay()
{
	Super::BeginPlay();

	// Give the ability to the unit
	GiveDefaultAbilities();

	// Ensure unit has an AI controller
	AUnitAIController* AIController = GetAIController();
	if (!AIController)
	{
		AIController = GetWorld()->SpawnActor<AUnitAIController>(AUnitAIController::StaticClass(), GetActorLocation(), GetActorRotation());

		if (AIController)
		{
			AIController->Possess(this);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[Unit] Failed to spawn AIController."));
			return;
		}
	}
	
	OnBeginPlay();
}

void AUnit::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// Initialize GAS: this unit is both the owner and avatar
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	AbilitySystemComponent->AddSet<UHealthAttributeSet>();
	AbilitySystemComponent->AddSet<UMoveAttributeSet>();
	// Initialize attributes
	InitDefaultAttributes();
}

void AUnit::InitializeDecal()
{
	// create the decal component
	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	// attach the decal to the root component
	DecalComponent->SetupAttachment(GetRootComponent());
	// get the collision radius from the capsule component
	const float Radius = GetCapsuleComponent()->GetScaledCapsuleRadius();
	// set the decal size
	constexpr float Scale = 5.0f; // Adjust the scale of the decal it is an number of experience
	DecalComponent->DecalSize = FVector(Radius * Scale, Radius * Scale, Radius * Scale);
	// set the rotation of the decal
	DecalComponent->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	// set the decal material
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DecalMaterial(TEXT("/Game/Material/Unit/M_SelectionDecal.M_SelectionDecal"));
	if (DecalMaterial.Succeeded())
	{
		DecalComponent->SetDecalMaterial(DecalMaterial.Object);
	}
	DecalComponent->SetVisibility(false);
}

void AUnit::InitializeAttributeSet()
{
	// Overriden by subclass
}

// GAS requirement
UAbilitySystemComponent* AUnit::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


// Gets the unit's AI controller
TObjectPtr<AUnitAIController> AUnit::GetAIController() const
{
	if (const APawn* AsPawn = Cast<APawn>(this))
	{
		return Cast<AUnitAIController>(AsPawn->GetController());
	}
	return nullptr;
}

// Command to move to a location
void AUnit::MoveToLocation(FVector TargetLocation)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("[Unit] MoveToLocation: No AI controller found."));
		return;
	}

	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	if (!MoveComp)
	{
		UE_LOG(LogTemp, Error, TEXT("[Unit] MoveToLocation: No movement component found."));
		return;
	}

	// Update movement speed from attribute set
	const UMoveAttributeSet* MoveAttributes = AbilitySystemComponent->GetSet<UMoveAttributeSet>();
	const float Speed = NUMERIC_VALUE(MoveAttributes, Speed);
	MoveComp->MaxWalkSpeed = Speed;

	// Move request
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation(TargetLocation);
	MoveRequest.SetAcceptanceRadius(50.f); // Adjustable per unit type

	FNavPathSharedPtr NavPath;
	const EPathFollowingRequestResult::Type MoveResult = AIController->MoveTo(MoveRequest, &NavPath);

	UE_LOG(LogTemp, Log, TEXT("[Unit] MoveToLocation → %s | Result: %d"), *TargetLocation.ToString(), (int32)MoveResult);
}

// Stops movement
void AUnit::StopMovement()
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->StopMovement();
	}
}

void AUnit::SetSelectedUnit(bool bSelected)
{
	DecalComponent->SetVisibility(bSelected);
}

// Grants default gameplay abilities to the unit
void AUnit::GiveDefaultAbilities()
{
	check(AbilitySystemComponent);

	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
	{
		const int32 InitLevel = 1;
		const FGameplayAbilitySpec AbilitySpec(AbilityClass, InitLevel);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

// Initializes base stats via a default effect
void AUnit::InitDefaultAttributes()
{
	if (!AbilitySystemComponent) return;

	InitializeAttributeSet();
}

void AUnit::SetAttributeSetByCurveTable(UCurveTable* DataTable, const FName& GroupName)
{
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("[Unit] SetAttributeSetByCurveTable: No AbilitySystemComponent found."));
		return;
	}
	FAttributeSetInitterDiscreteLevels AttributeSetInitter;
	TArray<UCurveTable*> CurveTables;
	CurveTables.Add(DataTable);

	AttributeSetInitter.PreloadAttributeSetData(CurveTables);
	AttributeSetInitter.InitAttributeSetDefaults(
		AbilitySystemComponent,
		GroupName,
		1, // Level
		true // Initial load
		);

	UE_LOG(LogTemp, Log, TEXT("[Unit] SetAttributeSetByCurveTable: %s"), *DataTable->GetName());
}
