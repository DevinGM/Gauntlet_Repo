// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerParent.h"

// Sets default values
APlayerParent::APlayerParent()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
 
// Called when the game starts or when spawned
void APlayerParent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Combine into a movement vector (in X/Y plane)
	FVector2D MoveDir2D(LastMovementInput.X, LastMovementInput.Y);

	if (!MoveDir2D.IsNearlyZero())
	{
		// Convert 2D vector to 3D facing direction
		FVector MoveDir3D = FVector(MoveDir2D.X, MoveDir2D.Y, 0.0f);
		FRotator TargetRotation = MoveDir3D.Rotation();

		// Smooth or snap
		FRotator SmoothRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 10.0f);
		SetActorRotation(SmoothRotation);
	}
}

// Default attack behavior — override in child classes if needed
void APlayerParent::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Base character attack!"));
}

// Move player up or down
void APlayerParent::MoveUpDown(float Value)
{
	if (Value != 0.0f)
	{
		const FVector Direction = FVector::ForwardVector;
		// divide moveSpeed by 600 because AddMovementInput defaults to 600
		// at a moveSpeed of 600, player moves at AddMovementInput's default speed
		AddMovementInput(Direction, Value * moveSpeed / 600.0f);

		// Update last movement input
		LastMovementInput.X = Value;
	}
	else
	{
		LastMovementInput.X = 0.0f;
	}
}

// Move player left or right
void APlayerParent::MoveLeftRight(float Value)
{
	if (Value != 0.0f)
	{
		const FVector Direction = FVector::RightVector;
		// divide moveSpeed by 600 because AddMovementInput defaults to 600
		// at a moveSpeed of 600, player moves at AddMovementInput's default speed
		AddMovementInput(Direction, Value * moveSpeed / 600.0f);

		// Update last movement input
		LastMovementInput.Y = Value;
	}
	else
	{
		LastMovementInput.Y = 0.0f;
	}
}

// call to damage the player by given amount
void APlayerParent::Damage(int Amount)
{
	currentHealth -= (Amount - armor);
	/////////////////////////////////////////////////////      PUT DEATH CODE HERE
	if (currentHealth < 0)
	{
	}
}

// call to heal the player by given amount
void APlayerParent::Heal(int Amount)
{
	currentHealth += Amount;
	// cap health at max health
	if (currentHealth > maxHealth)
		currentHealth = maxHealth;
}

// call to add given amount to player's score
void APlayerParent::AddScore(int Amount)
{
	score += Amount;
}

// called when player picks up item
void APlayerParent::OnItemPickUp(EItemType Item)
{
	if (Item == EItemType::HealthPickup)
	{
		////////////////////////////////////////////	DETERMINE ITEM HEAL AMOUNT HERE
		Heal(20);
	}

	if (Item == EItemType::ScorePickup)
	{
		////////////////////////////////////////////	DETERMINE ITEM SCORE AMOUNT HERE
		Heal(20);
	}
}