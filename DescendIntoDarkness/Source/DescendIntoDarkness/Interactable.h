// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class DESCENDINTODARKNESS_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }

	UFUNCTION(BlueprintPure, Category = "Interactable")
	bool IsActive();

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	void SetActive(bool NewState);

	UFUNCTION(BlueprintImplementableEvent)
    void Interact(APlayerController* Controller);

	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();

	virtual void WasCollected_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	FString GetUseText() const { return FString::Printf(TEXT("%s : Press C to %s"), *Name, *Action); }

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	FString GetItemName();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString Action;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool bIsActive;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh;

};
