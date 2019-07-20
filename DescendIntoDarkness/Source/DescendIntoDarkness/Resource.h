// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Resource.generated.h"


/**
 * 
 */

USTRUCT(BlueprintType)
struct FResource : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	FString ResourceName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	FName ResourceID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	int32 ResourceQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	UTexture2D* ResourceImage;
};

USTRUCT(BlueprintType)
struct FCraftable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Craftable)
	FString CraftableName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Craftable)
	FName CraftableID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Craftable)
	int32 CraftableQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Craftable)
	UTexture2D* CraftableImage;

	UPROPERTY(EditAnywhere, Category = Craftable)
	FResource Recipe[4];

};


UCLASS(BlueprintType)
class DESCENDINTODARKNESS_API UFResource : public UObject
{
	GENERATED_BODY()
	
};
