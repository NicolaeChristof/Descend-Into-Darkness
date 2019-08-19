// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
#include "Pickup.h"
#include "Resource.h"
#include "InventoryWidget.h"
#include "DescendIntoDarknessGameMode.h"
#include "DescendIntoDarknessCharacter.generated.h"






DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateInventoryDelegate, const TArray<FResource>&, InventoryItems);



UCLASS(config=Game)
class ADescendIntoDarknessCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;


	/** CollectionSphere*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CollectionSphere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollectionSphere;

    /** A sphere that allows the player to search for nearby camps */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camp", meta = (AllowPrivateAccess = "true"))
    class USphereComponent* CampCollisionSphere;


protected:

	void CheckForInteractables();

	void CheckForDialogue();
	/** Called for side to side input */
	//void MoveHorizontal(float Val);

    // Called for vertical movement on ropes
    void ClimbRope(float Val);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

    /** This is called when the player hits the correct button when near a camp spawn point */
    UFUNCTION(BlueprintCallable, Category = "Camp")
    void SpawnCamp();

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* CraftingDB;


public:
	ADescendIntoDarknessCharacter();

	virtual void Tick(float DeltaTime) override;
	
	void AddToInventory(FResource actor);

	UFUNCTION(BlueprintCallable)
	void UpdateInventory();

	UFUNCTION(BlueprintCallable)
	TArray<FResource> GetInventory();

	UFUNCTION(BlueprintCallable)
	TArray<FCraftable> GetCrafting();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateInventoryUI();

	class UDataTable* GetCraftingDB() const { return CraftingDB; }

	UFUNCTION(BlueprintCallable)
	void CraftItem(FCraftable item);

	bool CheckValidCraft(FCraftable item);

	UPROPERTY(BlueprintAssignable, Category = "Pickup")
	FUpdateInventoryDelegate OnUpdateInventory;
	

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


private:
	TArray<FResource> _inventory;

	class ANPC* CurrentNPC;

    /** Returns the camp collision sphere **/
    FORCEINLINE class USphereComponent* GetCampCollisionSphere() const { return CampCollisionSphere; }

    UPROPERTY(EditAnywhere, Category="Camp")
    TSubclassOf<class AActor> CampPrefab;

};
