#include "Miner.h"
#include "AshesOfWar/AI/AIControllers/UnitAIController.h"
#include "AshesOfWar/AI/StateTree/UnitStateTreeAIComponent.h"
#include "AshesOfWar/Resources/Management/UResourceComponent.h"
#include "AshesOfWar/Resources/Nodes/AResourceNode.h"
#include "AshesOfWar/Buildings/Base/ABaseBuilding.h"
#include "StateTree.h"

AMiner::AMiner()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the resource component (not attached to scene hierarchy)
	ResourceComponent = CreateDefaultSubobject<UResourceComponent>(TEXT("ResourceComponent"));
}

void AMiner::OnBeginPlay_Implementation()
{
	Super::OnBeginPlay_Implementation();

	AUnitAIController* AIController = GetAIController();
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("[Miner] Missing AIController"));
		return;
	}

	UUnitStateTreeAIComponent* StateTreeAIComponent = AIController->GetUnitStateTreeAIComponent();
	if (!StateTreeAIComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("[Miner] Missing StateTreeAIComponent"));
		return;
	}

	if (!MinerStateTreeAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("[Miner] No StateTree asset assigned"));
		return;
	}

	// Assign and start StateTree AI logic
	StateTreeAIComponent->SetStateTree(MinerStateTreeAsset);
	StateTreeAIComponent->StartLogic();
}

void AMiner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Priorité 1 : Construction
	if (ActiveConstructionTargets.Num() > 0)
	{
		for (int32 i = ActiveConstructionTargets.Num() - 1; i >= 0; --i)
		{
			AActor* Target = ActiveConstructionTargets[i];
			if (!Target)
			{
				ActiveConstructionTargets.RemoveAt(i);
				continue;
			}

			ABaseBuilding* Building = Cast<ABaseBuilding>(Target);
			if (!Building)
			{
				ActiveConstructionTargets.RemoveAt(i);
				continue;
			}

			if (Building->ConstructionProgress >= 1.f)
			{
				RemoveConstructionTarget(Building);
				continue;
			}

			float Distance = FVector::Dist(GetActorLocation(), Building->GetActorLocation());
			if (Distance <= ConstructionDistanceThreshold)
			{
				// Construire
				Building->ConstructionProgress += DeltaTime * ConstructionRate;

				// Clamp pour ne pas dépasser 1.0
				Building->ConstructionProgress = FMath::Clamp(Building->ConstructionProgress, 0.f, 1.f);

				// TODO: Appeler animation via Blueprint (ex: PlayConstructionAnimation)
			}
			else
			{
				// TODO: Déplacer automatiquement vers le bâtiment (MoveTo)
			}
		}

		return; // Ne mine pas si on est occupé à construire
	}

	// Priorité 2 : Mining automatique
	if (!ResourceComponent) return;

	AAResourceNode* Resource = ResourceComponent->GetCurrentResourceNode();
	if (Resource && FVector::Dist(GetActorLocation(), Resource->GetActorLocation()) < 150.f)
	{
		if (!ResourceComponent->IsCollecting())
		{
			MineResource();
		}
	}
}

void AMiner::MineResource()
{
	if (ResourceComponent)
	{
		ResourceComponent->BeginCollection();
	}
}

void AMiner::StopMining()
{
	if (ResourceComponent)
	{
		ResourceComponent->StopCollection();
	}
}

void AMiner::DepositCollectedResources()
{
	if (ResourceComponent)
	{
		ResourceComponent->DepositResources();
	}
}

void AMiner::SetCurrentResourceNode(AAResourceNode* NewNode)
{
	if (ResourceComponent)
	{
		ResourceComponent->SetCurrentResourceNode(NewNode);
	}
}

UResourceComponent* AMiner::GetResourceComponent() const
{
	return ResourceComponent;
}

void AMiner::AddConstructionTarget(AActor* Building)
{
	if (Building && !ActiveConstructionTargets.Contains(Building))
	{
		ActiveConstructionTargets.Add(Building);
	}
}

void AMiner::RemoveConstructionTarget(AActor* Building)
{
	if (Building)
	{
		ActiveConstructionTargets.Remove(Building);
	}
}

bool AMiner::IsConstructing() const
{
	return ActiveConstructionTargets.Num() > 0;
}
