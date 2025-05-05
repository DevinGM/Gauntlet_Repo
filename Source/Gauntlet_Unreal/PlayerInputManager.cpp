// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInputManager.h"

// Sets default values
APlayerInputManager::APlayerInputManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoReceiveInput = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APlayerInputManager::BeginPlay()
{
	Super::BeginPlay();
	
	EnableInput(GetWorld()->GetFirstPlayerController());
	SetupInputs(InputComponent);
}

// Called every frame
void APlayerInputManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerInputManager::SetupInputs(UInputComponent* InputComp)
{
	// player 1 inputs
	InputComp->BindAxis("UpDown_P1", this, &APlayerInputManager::MoveUpDownP1);
	InputComp->BindAxis("LeftRight_P1", this, &APlayerInputManager::MoveLeftRightP1);
	InputComp->BindAction("Attack_P1", IE_Pressed, this, &APlayerInputManager::AttackP1);
	// player 2 inputs
	InputComp->BindAxis("UpDown_P2", this, &APlayerInputManager::MoveUpDownP2);
	InputComp->BindAxis("LeftRight_P2", this, &APlayerInputManager::MoveLeftRightP2);
	InputComp->BindAction("Attack_P2", IE_Pressed, this, &APlayerInputManager::AttackP2);

	UE_LOG(LogTemp, Warning, TEXT("Input Manager has bound inputs"));
}

/// <summary>
/// player 1 actions
/// </summary>
void APlayerInputManager::MoveUpDownP1(float Value)
{
	if (Player1) Player1->MoveUpDown(Value);
}
void APlayerInputManager::MoveLeftRightP1(float Value)
{
	if (Player1) Player1->MoveLeftRight(Value);
}
void APlayerInputManager::AttackP1()
{
	if (Player1) Player1->Attack();
}

/// <summary>
/// player 2 actions
/// </summary>
void APlayerInputManager::MoveUpDownP2(float Value)
{
	if (Player2) Player2->MoveUpDown(Value);
}
void APlayerInputManager::MoveLeftRightP2(float Value)
{
	if (Player2) Player2->MoveLeftRight(Value);
}
void APlayerInputManager::AttackP2()
{
	if (Player2) Player2->Attack();
}