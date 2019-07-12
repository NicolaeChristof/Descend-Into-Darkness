// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CampSpawn.generated.h"

UCLASS()
class DESCENDINTODARKNESS_API ACampSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACampSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    bool HasBeenPlaced = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    FORCEINLINE  bool GetHasBeenPlaced() const { return HasBeenPlaced; }
    FORCEINLINE  void Place() { HasBeenPlaced = true; }

};
