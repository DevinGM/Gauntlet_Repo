// Fill out your copyright notice in the Description page of Project Settings.


#include "TestParentPlayer.h"

// Sets default values
ATestParentPlayer::ATestParentPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	playerNumber = 0;
}

// Called when the game starts or when spawned
void ATestParentPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestParentPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestParentPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

