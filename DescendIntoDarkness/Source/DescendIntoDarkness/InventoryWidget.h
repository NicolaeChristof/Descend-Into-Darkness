// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class DESCENDINTODARKNESS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

    public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Inventory")
	void LoadInventory();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Inventory")
	void LoadCrafting();
};
