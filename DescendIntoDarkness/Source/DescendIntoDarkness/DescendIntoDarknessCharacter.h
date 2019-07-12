// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

    /** A sphere that allows the player to search for nearby camps */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camp", meta = (AllowPrivateAccess = "true"))
    class USphereComponent* CampCollisionSphere;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

    /** This is called when the player hits the correct button when near a camp spawn point */
    UFUNCTION(BlueprintCallable, Category = "Camp")
    void SpawnCamp();


public:
	ADescendIntoDarknessCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    /** Returns the camp collision sphere **/
    FORCEINLINE class USphereComponent* GetCampCollisionSphere() const { return CampCollisionSphere; }

    UPROPERTY(EditAnywhere, Category="Camp")
    TSubclassOf<class AActor> CampPrefab;

};
