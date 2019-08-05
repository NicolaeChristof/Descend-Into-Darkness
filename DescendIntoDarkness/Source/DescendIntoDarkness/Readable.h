// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DescendIntoDarknessGameMode.h"
#include "Engine/World.h"
#include "Engine/DataTable.h"
#include "Resource.h"
#include "Readable.generated.h"

UCLASS()
class DESCENDINTODARKNESS_API AReadable : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReadable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Readable)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Readable)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Readable)
	int32 CurrentConversationID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Readable)
    int32 CurrentLineID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Readable)
	FText CurrentLine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Readable)
	bool bisActive;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetCurrentDialogue();

	bool GetNextDialogue();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDialogue();

	UFUNCTION(BlueprintImplementableEvent)
	void ClearDialogue();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
