#include "AResourceNode.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// --- Constructor ---
AAResourceNode::AAResourceNode()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create mesh component
	ResourceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ResourceMesh"));
	RootComponent = ResourceMesh;

	// Create collection zone
	CollectionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionRadius"));
	CollectionRadius->SetupAttachment(RootComponent);
	CollectionRadius->SetSphereRadius(200.f);
	CollectionRadius->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollectionRadius->SetCollisionObjectType(ECC_WorldDynamic);
	CollectionRadius->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollectionRadius->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Defaults
	ResourceType = EResourceType::Aetherium;
	QteDisponible = 1000;
	ExtractionRate = 10;
}

// --- Getters / Setters ---
int AAResourceNode::GetQteDisponible()
{
	return QteDisponible;
}

int AAResourceNode::GetExtRate()
{
	return ExtractionRate;
}

void AAResourceNode::SetQteDisponible(int Amount)
{
	QteDisponible = Amount;
}

// --- Consume Resource ---
void AAResourceNode::ConsumeResource(float Amount)
{
	
	const int32 AmountInt = FMath::RoundToInt(Amount);
	const int32 PreviousQte = QteDisponible;
	QteDisponible = FMath::Clamp(QteDisponible - AmountInt, 0, QteDisponible);

#if WITH_EDITOR
	FString OwnerName = GetOwner() ? GetOwner()->GetName() : TEXT("None");
	UE_LOG(LogTemp, Log, TEXT("[ResourceNode] %s consumed %d units. Remaining: %d (from %d)"),
		*OwnerName, AmountInt, QteDisponible, PreviousQte);
#endif
}


