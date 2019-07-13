// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Resource.generated.h"

/**
 * 
 */


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
	UTexture2D* ResourceImage;

};
