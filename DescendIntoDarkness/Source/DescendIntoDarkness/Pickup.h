// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Pickup.generated.h"

/**
 * 
 */
UCLASS()
class DESCENDINTODARKNESS_API APickup : public AInteractable
{
	GENERATED_BODY()
	
public:

    APickup();

	void Show(bool visible);
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	/** Override the WasCollected function - use Implementation because it's a Blueprint Native Event */
	void WasCollected_Implementation() override;

private:
	
};
