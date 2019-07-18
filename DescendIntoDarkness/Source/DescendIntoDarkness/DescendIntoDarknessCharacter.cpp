// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DescendIntoDarknessCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Engine/World.h"
#include "Interactable.h"
#include "Classes/Components/SphereComponent.h"
#include "NewCampSpawnPole.h"


ADescendIntoDarknessCharacter::ADescendIntoDarknessCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;


	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);

    // Create the collision sphere
    CampCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CampCollsionSphere"));
    CampCollisionSphere->SetupAttachment(RootComponent);
    CampCollisionSphere->SetSphereRadius(250.f);


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADescendIntoDarknessCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ADescendIntoDarknessCharacter::CheckForInteractables);
	PlayerInputComponent->BindAction("PlaceCamp", IE_Released, this, &ADescendIntoDarknessCharacter::SpawnCamp);

    //PlayerInputComponent->BindAxis("MoveHorizontal", this, &ADescendIntoDarknessCharacter::MoveHorizontal);
    PlayerInputComponent->BindAxis("ClimbRope", this, &ADescendIntoDarknessCharacter::ClimbRope);

}

//tick function
void ADescendIntoDarknessCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADescendIntoDarknessCharacter::CheckForInteractables()
{

	//get all overlapping actors and store them in an array
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors, AInteractable::StaticClass());

	UE_LOG(LogClass, Log, TEXT("OverlappingActors: %d"), CollectedActors.Num());


	if (CollectedActors.Num() >= 1) {
		AInteractable* const TestPickup = Cast<AInteractable>(CollectedActors[0]);
		if (TestPickup && !TestPickup->IsPendingKill() && TestPickup->IsActive())
		{
			// Call the Pickup was collected
			TestPickup->WasCollected();
			//Deactivate the pickup
			TestPickup->SetActive(false);
		}
	}


	/**
	//For each actor we collect
	for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected) {
		//Cast the actor to APickup
		AInteractable* const TestPickup = Cast<AInteractable>(CollectedActors[iCollected]);
		// If the cast is sucessful and the pickup in valid and active
		if (TestPickup && !TestPickup->IsPendingKill() && TestPickup->IsActive())
		{
			// Call the Pickup was collected
			TestPickup->WasCollected();
			//Deactivate the pickup
			TestPickup->SetActive(false);
		}

	}
	*/

}

void ADescendIntoDarknessCharacter::AddToInventory(FSResource actor)
{
	_inventory.Add(actor);
	UpdateInventory();
}

TArray<FSResource> ADescendIntoDarknessCharacter::GetInventory() 
{
	return _inventory;
}

void ADescendIntoDarknessCharacter::UpdateInventory() 
{
	
	FString sInventory = "";

	for (FSResource actor : _inventory)
	{
		sInventory.Append(actor.ResourceName);
		sInventory.Append(" | ");
	}

	GEngine->AddOnScreenDebugMessage(1, 3, FColor::White, *sInventory);
	

	OnUpdateInventory.Broadcast(_inventory);
}



void ADescendIntoDarknessCharacter::ClimbRope(float value)
{
    // add movement in that direction
    AddMovementInput(FVector(0.f,0.f,1.f), value);
}


void ADescendIntoDarknessCharacter::SpawnCamp()
{
    if (CampPrefab) {
        // This stores all the actors that are within the collection sphere
        TArray<AActor*> NearbyActors;
        CampCollisionSphere->GetOverlappingActors(NearbyActors);
        for (int32 iCollected = 0; iCollected < NearbyActors.Num(); ++iCollected) {
            ANewCampSpawnPole* const TestCampSpawn = Cast<ANewCampSpawnPole>(NearbyActors[iCollected]);
            if (TestCampSpawn && !TestCampSpawn->IsPendingKill() && !TestCampSpawn->GetHasBeenPlaced()) {
                UWorld* world = GetWorld();

                if (world) {
                    TestCampSpawn->Place();
                    FActorSpawnParameters spawnParams;
                    spawnParams.Owner = this;

                    FRotator spawnRotation(0.f);
                    FVector spawnLocation = TestCampSpawn->GetActorLocation();
                    world->SpawnActor<AActor>(CampPrefab, spawnLocation, spawnRotation, spawnParams);
                }
            }
        }
    }
}

