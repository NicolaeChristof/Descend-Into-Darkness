// Fill out your copyright notice in the Description page of Project Settings.


#include "Readable.h"

// Sets default values
AReadable::AReadable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Name = "Note";
	CurrentLineID = 1;
	bisActive = false;
}

// Called when the game starts or when spawned
void AReadable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReadable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReadable::GetCurrentDialogue()
{
	ADescendIntoDarknessGameMode* gm = (ADescendIntoDarknessGameMode*)GetWorld()->GetAuthGameMode();
    UDataTable* tempDB = gm->DialogueDB;

	TArray<FName> RowNames = tempDB->GetRowNames();

	for (FName Row : RowNames)
	{
		UE_LOG(LogClass, Log, TEXT("Row Name: %s"), *Row.ToString());
		FDialogue* tempLine = tempDB->FindRow<FDialogue>(Row, "");
		if (tempLine)
		{
			if (ID == tempLine->NPCID)
			{
				CurrentLine = tempLine->Dialogue;
				UpdateDialogue();
				break;
			}
		}
	}
}
