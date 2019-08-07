// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Name = "Note";
	CurrentLineID = 1;
	bisActive = false;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC::GetCurrentDialogue()
{
	ADescendIntoDarknessGameMode* gm = (ADescendIntoDarknessGameMode*)GetWorld()->GetAuthGameMode();
    UDataTable* tempDB = gm->DialogueDB;

	TArray<FName> RowNames = tempDB->GetRowNames();
	UE_LOG(LogClass, Log, TEXT("Row Size: %d"), RowNames.Num());
	for (FName Row : RowNames)
	{
		UE_LOG(LogClass, Log, TEXT("Row Name: %s"), *Row.ToString());
		FDialogue* tempLine = tempDB->FindRow<FDialogue>(Row, "");
		if (tempLine)
		{
			if (ID == tempLine->NPCID)
			{
				CurrentLine = tempLine->Dialogue;
				CurrentConversationID = tempLine->ConversationID;
				CurrentLineID = tempLine->LineID;
				UpdateDialogue();
				break;
			}
		}
	}
}

bool ANPC::GetNextDialogue()
{
	ADescendIntoDarknessGameMode* gm = (ADescendIntoDarknessGameMode*)GetWorld()->GetAuthGameMode();
	UDataTable* tempDB = gm->DialogueDB;

	TArray<FName> RowNames = tempDB->GetRowNames();
	UE_LOG(LogClass, Log, TEXT("Row Size: %d"), RowNames.Num());
	for (FName Row : RowNames)
	{
		UE_LOG(LogClass, Log, TEXT("Row Name: %s"), *Row.ToString());
		FDialogue* tempLine = tempDB->FindRow<FDialogue>(Row, "");
		if (tempLine)
		{
			if (ID == tempLine->NPCID && CurrentConversationID == tempLine->ConversationID)
			{
				if ((CurrentLineID + 1) == tempLine->LineID)
				{
					CurrentLine = tempLine->Dialogue;
					CurrentLineID = tempLine->LineID;
					UpdateDialogue();
					return true;
				}
			}
		}
	}
	
	ClearDialogue();
	return false;
}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
