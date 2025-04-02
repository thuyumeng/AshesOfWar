#pragma once

#include "CoreMinimal.h"
#include "FPlayerResourceData.generated.h"

//* Struct contenant les ressources individuelles d’un joueur *//
USTRUCT(BlueprintType)
struct RTS_EPICCONQUEST_API FPlayerResourceData
{
	GENERATED_BODY()

	// Quantité d’Aetherium
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int32 Aetherium = 0;

	// Quantité de Vitae
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int32 Vitae = 0;

	// Quantité d’Umbra
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int32 Umbra = 0;
};
