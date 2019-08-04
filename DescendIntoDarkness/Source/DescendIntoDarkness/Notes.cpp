// Fill out your copyright notice in the Description page of Project Settings.


#include "Notes.h"

// Sets default values
ANotes::ANotes()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANotes::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANotes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANotes::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

