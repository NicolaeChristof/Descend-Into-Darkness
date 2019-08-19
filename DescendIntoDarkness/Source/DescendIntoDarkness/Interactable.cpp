// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInteractable::AInteractable()
{
 	
	Name = "Name not set";
	Action = "Interact";
	bIsActive = true;
	bIsNote = false;
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
}

//test comment
// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}


bool AInteractable::IsActive()
{
	return bIsActive;
}

bool AInteractable::IsNote()
{
	return bIsNote;
}

void AInteractable::SetActive(bool NewPickupState)
{
	bIsActive = NewPickupState;
}

void AInteractable::WasCollected_Implementation()
{
	FString PickupDebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("You have collected %s"), *PickupDebugString);
}

FString AInteractable::GetInteractableName()
{
	return Name;
}

