// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "DescendIntoDarknessGameMode.h"
#include "Engine/World.h"
#include "Engine/DataTable.h"
#include "Resource.h"
#include "Notes.generated.h"

/**
 * 
 */
UCLASS()
class DESCENDINTODARKNESS_API ANotes : public AInteractable
{
	GENERATED_BODY()
	
public:

	ANotes();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	int32 NoteID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
	int32 CurrentLineID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
	FText CurrentLine;

	UFUNCTION(BlueprintCallable, Category = Pickup)
	FString GetNoteName();

	/** Override the WasCollected function - use Implementation because it's a Blueprint Native Event */
	void WasCollected_Implementation() override;
};
