// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "NPC.generated.h"

/**
 * 
 */
UCLASS()
class DESCENDINTODARKNESS_API ANPC : public AInteractable
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Dialogue;

};
