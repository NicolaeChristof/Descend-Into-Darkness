// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/DataTable.h"
#include "Resource.h"
#include "Notes.h"
#include "DescendIntoDarknessGameMode.generated.h"

UCLASS(minimalapi)
class ADescendIntoDarknessGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADescendIntoDarknessGameMode();

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* DialogueDB;

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* NoteDB;

	UFUNCTION(BlueprintCallable, Category = Notes)
	void AddToNotes(FNoteContent Note);

	UFUNCTION(BlueprintCallable, Category = Notes)
	TArray<FNoteContent> GetNotes();

protected:

private:
	TArray<FNoteContent> Notes;
};



