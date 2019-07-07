// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

APickup::APickup()
{

	ItemID = FName("Please enter an ID");
}

//destroy when picked up
void APickup::WasCollected_Implementation() {

	// Use the base pickup behavior
	Super::WasCollected_Implementation();
	// Destroy the battery
	Destroy();
}
