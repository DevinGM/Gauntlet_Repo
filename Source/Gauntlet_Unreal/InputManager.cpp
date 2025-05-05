// Fill out your copyright notice in the Description page of Project Settings.

#include "InputManager.h"

// Sets default values
AInputManager::AInputManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoReceiveInput = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AInputManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInputManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AInputManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// player 1 inputs
	PlayerInputComponent->BindAxis("UpDown_P1", this, &AInputManager::MoveUpDownP1);
	PlayerInputComponent->BindAxis("LeftRight_P1", this, &AInputManager::MoveLeftRightP1);
	PlayerInputComponent->BindAction("Attack_P1", IE_Pressed, this, &AInputManager::AttackP1);
	// player 2 inputs
	PlayerInputComponent->BindAxis("UpDown_P2", this, &AInputManager::MoveUpDownP2);
	PlayerInputComponent->BindAxis("LeftRight_P2", this, &AInputManager::MoveLeftRightP2);
	PlayerInputComponent->BindAction("Attack_P2", IE_Pressed, this, &AInputManager::AttackP2);

	UE_LOG(LogTemp, Warning, TEXT("Input Manager has bound inputs"));
}

/// <summary>
/// player 1 actions
/// </summary>
void AInputManager::MoveUpDownP1(float Value)
{
	if (Player1) Player1->MoveUpDown(Value);
}
void AInputManager::MoveLeftRightP1(float Value)
{
	if (Player1) Player1->MoveLeftRight(Value);
}
void AInputManager::AttackP1()
{
	if (Player1) Player1->Attack();
}

/// <summary>
/// player 2 actions
/// </summary>
void AInputManager::MoveUpDownP2(float Value)
{
	if (Player2) Player2->MoveUpDown(Value);
}
void AInputManager::MoveLeftRightP2(float Value)
{
	if (Player2) Player2->MoveLeftRight(Value);
}
void AInputManager::AttackP2()
{
	if (Player2) Player2->Attack();
}