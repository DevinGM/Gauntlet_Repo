// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerParent.h"

// Sets default values
APlayerParent::APlayerParent()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
}
 
// Called when the game starts or when spawned
void APlayerParent::BeginPlay()
{
	Super::BeginPlay();
}

/*// Called every frame
void APlayerParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}*/

// Default attack behavior — override in child classes if needed
void APlayerParent::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Base character attack!"));
}

// Move player in given direction
void  APlayerParent::MoveInDirection(FVector Direction, float DeltaTime)
{
	if (Direction.IsNearlyZero()) return;

	// normalize direction for rotation
	FVector NormalizedDirection = Direction.GetSafeNormal();
	FRotator TargetRotation = NormalizedDirection.Rotation();

	// keep only yaw rotation (avoid pitch/roll tilting)
	TargetRotation = FRotator(0.0f, TargetRotation.Yaw, 0.0f);

	// interpolate from current to target rotation
	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 10.0f); // 10 = rotation speed
	SetActorRotation(NewRotation);

	// calculate movement
	FVector TargetLocation = GetActorLocation() + Direction * moveSpeed * DeltaTime;

	// clamp to camera bounds
	AMultiPlayerCamera* Camera = AMultiPlayerCamera::GetActiveCamera(GetWorld());
	if (Camera)
	{
		TargetLocation = Camera->ClampWorldPositionToView(TargetLocation, 50.0f); // 50 = padding
	}

	// set location
	SetActorLocation(TargetLocation);
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