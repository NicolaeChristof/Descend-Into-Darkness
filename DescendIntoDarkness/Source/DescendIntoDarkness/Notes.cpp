// Fill out your copyright notice in the Description page of Project Settings.


#include "Notes.h"

ANotes::ANotes()
{
	bIsNote = false;
}

/** Override the WasCollected function - use Implementation because it's a Blueprint Native Event */
void ANotes::WasCollected_Implementation()
{
	ADescendIntoDarknessGameMode* gm = (ADescendIntoDarknessGameMode*)GetWorld()->GetAuthGameMode();
	UDataTable* tempDB = gm->NoteDB;
	TArray<FName> RowNames = tempDB->GetRowNames();
	UE_LOG(LogClass, Log, TEXT("Row Size: %d"), RowNames.Num());
	for (FName Row : RowNames)
	{
		UE_LOG(LogClass, Log, TEXT("Row Name: %s"), *Row.ToString());
		FNoteContent* tempLine = tempDB->FindRow<FNoteContent>(Row, "");
		if (tempLine)
		{
			if (NoteID == tempLine->NoteID)
			{
				FNoteContent temp;
				temp.Name = tempLine->Name;
				temp.NoteID = tempLine->NoteID;
				temp.LineID = tempLine->LineID;
				temp.Text = tempLine->Text;
				gm->AddToNotes(temp);
				break;
			}
		}
	}

	Destroy();
	gm->UpdateNoteUI();
}

FString ANotes::GetNoteName()
{
	return Name;
}