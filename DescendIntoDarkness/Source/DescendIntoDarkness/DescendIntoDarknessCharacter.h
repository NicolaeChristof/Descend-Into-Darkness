// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
#include "Pickup.h"
#include "DescendIntoDarknessCharacter.generated.h"








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

protected:

	void CheckForInteractables();

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	ADescendIntoDarknessCharacter();

	virtual void Tick(float DeltaTime) override;
	
	void AddToInventory(APickup* actor);

	UFUNCTION(BlueprintCallable)
	void PrintInventory();
	
	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	TArray<APickup*> _inventory;
};
