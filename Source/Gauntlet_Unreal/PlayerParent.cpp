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

	// set health drain timer
	if (GetWorld())
		GetWorld()->GetTimerManager().SetTimer(HealthDrainTimer, this, &APlayerParent::HealthDrain, 2.0f, true);
}

/*// Called every frame
void APlayerParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}*/

// spawn a bullet in direction player is facing
void APlayerParent::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Base character attack!"));

	if (!BulletClass) return;

	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
	FRotator SpawnRotation = GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	ABulletParent* Bullet = GetWorld()->SpawnActor<ABulletParent>(BulletClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (Bullet)
	{
		Bullet->Direction = GetActorForwardVector();
		Bullet->Direction = Bullet->Direction.GetSafeNormal();
		Bullet->Damage = damage;
		Bullet->Player = this;
	}
}

// move player in given direction
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
void APlayerParent::DealDamageToPlayer(int Amount, bool IsTimerDamage)
{
	if (IsTimerDamage)
		currentHealth -= Amount;
	else if (!OnDamageCooldown)
	{
		currentHealth -= (Amount - armor);
		// start damage cooldown
		if (GetWorld())
		{
			OnDamageCooldown = true;
			GetWorld()->GetTimerManager().SetTimer(DamageCoolDownTimer, this, &APlayerParent::DamageCooldown, 2.0f, false);
		}
	}

	if (currentHealth < 0)
	{
		////////////////      PUT DEATH CODE HERE
		Destroy();

		// set health drain timer
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(HealthDrainTimer);
			GetWorld()->GetTimerManager().ClearTimer(DamageCoolDownTimer);
		}
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
	// if item is health pickup heal
	if (Item == EItemType::HealthPickup)
		////////////////	DETERMINE ITEM HEAL AMOUNT HERE
		Heal(20);

	// if item is score pickup add to score
	if (Item == EItemType::ScorePickup)
		////////////////	DETERMINE ITEM SCORE AMOUNT HERE
		AddScore(20);

	// if item is key pickup increment KeysHeld
	if (Item == EItemType::KeyPickup)
		KeysHeld++;
}

// deal 1 damage to the player bypassing armor
void APlayerParent::HealthDrain()
{
	DealDamageToPlayer(1, true);
}

// turn off damage cooldown
void APlayerParent::DamageCooldown()
{
	OnDamageCooldown = false;
}