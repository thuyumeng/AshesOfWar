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
	QteDisponible = 1000.f;
	ExtractionRate = 10.f;
}

// --- Getters / Setters ---
float AAResourceNode::GetQteDisponible()
{
	return QteDisponible;
}

float AAResourceNode::GetExtRate()
{
	return ExtractionRate;
}

void AAResourceNode::SetQteDisponible(int Amount)
{
	QteDisponible = Amount;
}

// --- Consume Resource ---
float AAResourceNode::ConsumeResource(float Amount)
{
	Amount = FMath::Min(Amount, QteDisponible);
	QteDisponible -= Amount;

#if WITH_EDITOR
	FString OwnerName = GetOwner() ? GetOwner()->GetName() : TEXT("None");
	// UE_LOG(LogTemp, Log, TEXT("[ResourceNode] %s consumed %f units. Remaining: %f"),
	// 	*OwnerName, Amount, QteDisponible);
#endif
	return Amount;
}


