// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Name = "NPC";
	CurrentConversationID = 1;
	CurrentLineID = 1;
	bisPlayerTalking = false;
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
			if (ID == tempLine->NPCID && CurrentConversationID == tempLine->ConversationID && tempLine->bIsRoot && CurrentLineID == tempLine->LineID)
			{
				CurrentLine = tempLine->Dialogue;
				CurrentConversationID = tempLine->ConversationID;
				CurrentLineID = tempLine->LineID;
				NextNodes = tempLine->AdjacencyNodes;
				UpdateDialogue();
				break;
			}
		}
	}
}

bool ANPC::GetNextDialogue()
{
	//check if there are no more dialogue choices
	if (NextNodes.Equals("0"))
	{
		ClearDialogue();
		CurrentLineID = 1;
		return false;
	}
	else if (NextNodes.Contains("/"))
	{
		DialogueChoices.Empty();
		bisPlayerTalking = true;
		FString temp = NextNodes;
		while (temp.Contains("/"))
		{
			int32 index = temp.Contains("/");
			GetLineByID((temp.Mid(0,index)));
			UE_LOG(LogClass, Log, TEXT("Left side Chop : %s"), *temp.Mid(0,index));
			temp = temp.Mid(index+1,temp.Len()-1);
			UE_LOG(LogClass, Log, TEXT("Right side Chop : %s"), *temp);
			
		}
		GetLineByID(temp);
		
		DisplayPlayerChoices();
		return true;
	}
	else
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
					if ((FCString::Atoi(*NextNodes)) == tempLine->LineID)
					{
						CurrentLine = tempLine->Dialogue;
						CurrentLineID = tempLine->LineID;
						NextNodes = tempLine->AdjacencyNodes;
						UpdateDialogue();
						return true;
					}
				}
			}
		}

		ClearDialogue();
		return false;
	}
	
}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::GetLineByID(FString Line)
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
				if ((FCString::Atoi(*Line)) == tempLine->LineID)
				{
					FDialogue choice;
					choice.NPCID = tempLine->NPCID;
					choice.ConversationID = tempLine->ConversationID;
					choice.LineID = tempLine->LineID;
					choice.AdjacencyNodes = tempLine->AdjacencyNodes;
					choice.Dialogue = tempLine->Dialogue;
					DialogueChoices.Add(choice);
					break;
				}
			}
		}
	}
}

void ANPC::GetNPCResponse(FDialogue PlayerResponse)
{
	ClearDialogue();
	CurrentConversationID = PlayerResponse.ConversationID;
	CurrentLineID = PlayerResponse.LineID;
	NextNodes = PlayerResponse.AdjacencyNodes;
	bisPlayerTalking = false;
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
				if ((FCString::Atoi(*NextNodes)) == tempLine->LineID)
				{
					CurrentLine = tempLine->Dialogue;
					CurrentLineID = tempLine->LineID;
					NextNodes = tempLine->AdjacencyNodes;
					UpdateDialogue();
					break;
				}
			}
		}
	}
}