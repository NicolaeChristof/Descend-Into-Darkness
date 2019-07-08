// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "DescendIntoDarknessCharacter.h"
#include "Kismet/GameplayStatics.h"

APickup::APickup()
{

	ItemID = FName("Please enter an ID");
}

//destroy when picked up
void APickup::WasCollected_Implementation() {

	// Use the base pickup behavior
	Super::WasCollected_Implementation();
	ADescendIntoDarknessCharacter* player = Cast< ADescendIntoDarknessCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	//Add to Inventory
	if (player)
	{
		player->AddToInventory(this);
	}
	// Destroy the battery
	//Destroy();
}

void APickup::Show(bool visible)
{
	
}
