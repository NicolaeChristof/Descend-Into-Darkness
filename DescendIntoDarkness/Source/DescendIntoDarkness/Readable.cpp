// Fill out your copyright notice in the Description page of Project Settings.


#include "Readable.h"

// Sets default values
AReadable::AReadable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

