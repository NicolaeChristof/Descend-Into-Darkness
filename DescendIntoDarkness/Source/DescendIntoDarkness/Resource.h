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

/**
UCLASS(BlueprintType)
class DESCENDINTODARKNESS_API UResource : public UObject
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
*/