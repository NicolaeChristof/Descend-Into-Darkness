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
#include "NPC.h"
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
	PlayerInputComponent->BindAction("Talk", IE_Pressed, this, &ADescendIntoDarknessCharacter::CheckForDialogue);
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
			TestPickup->Interact();
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

void ADescendIntoDarknessCharacter::CheckForDialogue()
{
	UE_LOG(LogClass, Log, TEXT("Test"));

	//get all overlapping actors and store them in an array
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors, ANPC::StaticClass());
	UE_LOG(LogClass, Log, TEXT("OverlappingActors: %d"), CollectedActors.Num());

	if (CollectedActors.Num() >= 1) {
		
		if (CurrentNPC != Cast<ANPC>(CollectedActors[0]))
		{
			CurrentNPC = Cast<ANPC>(CollectedActors[0]);
			CurrentNPC->GetCurrentDialogue();
		}
		else
		{
			if (CurrentNPC)
			{
				if (!CurrentNPC->GetNextDialogue())
				{
					CurrentNPC = NULL;
				}
			}
		}
		
	}
	else
	{
		if (CurrentNPC)
		{
			CurrentNPC->ClearDialogue();
		}
	}
	
}

void ADescendIntoDarknessCharacter::AddToInventory(FResource actor)
{
	if (_inventory.Num() == 0)
	{
		_inventory.Add(actor);
	}
	else
	{
		bool bIsFound = false;
		for (int32 i = 0; i < _inventory.Num(); ++i) 
		{
			if (_inventory[i].ResourceID == actor.ResourceID)
			{
				_inventory[i].ResourceQuantity += actor.ResourceQuantity;
				UE_LOG(LogClass, Log, TEXT("Quantity: %d"), _inventory[i].ResourceQuantity);
				bIsFound = true;
			}
		}

		if (!bIsFound)
		{
			_inventory.Add(actor);
		}
	}
	UpdateInventory();
}

TArray<FResource> ADescendIntoDarknessCharacter::GetInventory() 
{
	return _inventory;
}

TArray<FCraftable> ADescendIntoDarknessCharacter::GetCrafting()
{
	TArray<FName> RowNames = CraftingDB->GetRowNames();
	TArray<FCraftable> ValidCraftables;

	
	for (FName Row : RowNames)
	{
		UE_LOG(LogClass, Log, TEXT("Row Name: %s"), *Row.ToString());
		FCraftable* Recipe = CraftingDB->FindRow<FCraftable>(Row, "");
		if (Recipe)
		{
			ValidCraftables.Add(*Recipe);
		}
		
	}



	return ValidCraftables;
}

void ADescendIntoDarknessCharacter::UpdateInventory() 
{
	
	FString sInventory = "";

	for (FResource actor : _inventory)
	{
		sInventory.Append(actor.ResourceName);
		sInventory.Append(" | ");
	}

	GEngine->AddOnScreenDebugMessage(1, 3, FColor::White, *sInventory);
	UpdateInventoryUI();
	OnUpdateInventory.Broadcast(_inventory);
}

void ADescendIntoDarknessCharacter::CraftItem(FCraftable item)
{
	if (CheckValidCraft(item))
	{
		for (int i = 0; i < 4; ++i)
		{
			FName id = item.Recipe[i].ResourceID;

			if (id == "None")
			{
				break;
			}

			for (int j = 0; j < _inventory.Num(); ++j)
			{
				if (id == _inventory[j].ResourceID)
				{
					int32 quantity = item.Recipe[i].ResourceQuantity;
					_inventory[j].ResourceQuantity -= quantity;
					break;
				}
			}
		}

		UE_LOG(LogClass, Log, TEXT("Item Crafted"));

		FResource temp;
		temp.ResourceName = item.CraftableName;
		temp.ResourceID = item.CraftableID;
		temp.ResourceImage = item.CraftableImage;
		temp.ResourceQuantity = item.CraftableQuantity;
		_inventory.Add(temp);
		UpdateInventory();
	}
	else
	{
		UE_LOG(LogClass, Log, TEXT("Item Failed"));
		return;
	}
}

bool ADescendIntoDarknessCharacter::CheckValidCraft(FCraftable item)
{
	int32 i = 0;
	FName id = item.Recipe[i].ResourceID;
	int32 quantity = item.Recipe[i].ResourceQuantity;
	
	while (id != "None" && i < 4)
	{
		
		bool bIsFound = false;
		for (int j = 0; j < _inventory.Num(); ++j)
		{
			if (id == _inventory[j].ResourceID) 
			{
				bIsFound = true;
				if (quantity > _inventory[j].ResourceQuantity)
				{
					return false;
				}
			}
		}

		if (!bIsFound)
		{
			return false;
		}
		++i;
		if (i < 4)
		{
			id = item.Recipe[i].ResourceID;
		}
		
	}

	return true;
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

