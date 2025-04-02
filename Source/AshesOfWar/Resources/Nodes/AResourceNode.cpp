#include "AResourceNode.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

AAResourceNode::AAResourceNode()
{
	// Disable Tick by default
	PrimaryActorTick.bCanEverTick = false;

	// Create the visual mesh component
	ResourceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ResourceMesh"));
	RootComponent = ResourceMesh;

	// Create the collection detection radius (for workers)
	CollectionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionRadius"));
	CollectionRadius->SetupAttachment(RootComponent);
	CollectionRadius->SetSphereRadius(200.f); // Default radius, adjustable in editor
	CollectionRadius->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollectionRadius->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollectionRadius->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollectionRadius->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	// Default values
	ResourceType = EResourceType::Aetherium;
	QteDisponible = 1000;
	ExtractionRate = 10;
}

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
