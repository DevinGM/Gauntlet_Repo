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
	//Super::Tick(DeltaTime);
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
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// divide moveSpeed by 600 because AddMovementInput defaults to 600
		// at a moveSpeed of 600, player moves at AddMovementInput's default speed
		AddMovementInput(Direction, Value * moveSpeed / 600.0f);
	}
}

// Move player left or right
void APlayerParent::MoveLeftRight(float Value)
{
	if (Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// divide moveSpeed by 600 because AddMovementInput defaults to 600
		// at a moveSpeed of 600, player moves at AddMovementInput's default speed
		AddMovementInput(Direction, Value * moveSpeed / 600.0f);
	}
}