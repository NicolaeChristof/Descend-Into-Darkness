// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DescendIntoDarknessGameMode.h"
#include "DescendIntoDarknessCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADescendIntoDarknessGameMode::ADescendIntoDarknessGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADescendIntoDarknessGameMode::AddToNotes(ANotes Note)
{
	Notes.Add(Note);
}

TArray<ANotes> ADescendIntoDarknessGameMode::GetNotes()
{
	return Notes;
}
