// Fill out your copyright notice in the Description page of Project Settings.

/// <summary>
/// Devin G Monaghan 
/// 5/14/2025
/// Handles input management
/// Instantiates HUD
/// </summary>

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
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

	// find all player characters
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerParent::StaticClass(), PlayerArray);
	// store all players
	// activate each player 
	if (PlayerArray.IsValidIndex(0))
	{
		Player1 = Cast<APlayerParent>(PlayerArray[0]);

	}
	if (PlayerArray.IsValidIndex(1))
	{
		Player2 = Cast<APlayerParent>(PlayerArray[1]);

	}
	if (PlayerArray.IsValidIndex(2))
	{
		Player3 = Cast<APlayerParent>(PlayerArray[2]);

	}
	if (PlayerArray.IsValidIndex(3))
	{
		Player4 = Cast<APlayerParent>(PlayerArray[3]);

	}
	
	EnableInput(GetWorld()->GetFirstPlayerController());
	SetupInputs(InputComponent);

	if (HUDClassRef)
	{
		UUserWidget* HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDClassRef);

		if (HUDWidget)
		{
			UHUD_Parent* HUD = Cast<UHUD_Parent>(HUDWidget);
			if (HUD)
			{
				HUD->AddToViewport();
				HUD->InputManagerReference = this;
			}
		}
	}
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
	// player 3 inputs
	InputComp->BindAxis("UpDown_P3", this, &APlayerInputManager::MoveUpDownP3);
	InputComp->BindAxis("LeftRight_P3", this, &APlayerInputManager::MoveLeftRightP3);
	InputComp->BindAction("Attack_P3", IE_Pressed, this, &APlayerInputManager::AttackP3);
	// player 4 inputs
	InputComp->BindAxis("UpDown_P4", this, &APlayerInputManager::MoveUpDownP4);
	InputComp->BindAxis("LeftRight_P4", this, &APlayerInputManager::MoveLeftRightP4);
	InputComp->BindAction("Attack_P4", IE_Pressed, this, &APlayerInputManager::AttackP4);

	UE_LOG(LogTemp, Warning, TEXT("Input Manager has bound inputs"));
}

/// <summary>
/// player 1 actions
/// </summary>
void APlayerInputManager::MoveUpDownP1(float Value)
{
	if (!Player1 || Value == 0.0f) return;

	float DeltaTime = GetWorld()->GetDeltaSeconds();
	Player1->MoveInDirection(FVector(FVector::ForwardVector * Value), DeltaTime);
}
void APlayerInputManager::MoveLeftRightP1(float Value)
{
	if (!Player1 || Value == 0.0f) return;

	float DeltaTime = GetWorld()->GetDeltaSeconds();
	Player1->MoveInDirection(FVector(FVector::RightVector * Value), DeltaTime);
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
	if (!Player2 || Value == 0.0f) return;

	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	Player2->MoveInDirection(FVector(FVector::ForwardVector * Value), DeltaTime);
}
void APlayerInputManager::MoveLeftRightP2(float Value)
{
	if (!Player2 || Value == 0.0f) return;

	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	Player2->MoveInDirection(FVector(FVector::RightVector * Value), DeltaTime);
}
void APlayerInputManager::AttackP2()
{
	if (Player2) Player2->Attack();
}

/// <summary>
/// player 3 actions
/// </summary>
void APlayerInputManager::MoveUpDownP3(float Value)
{
	if (!Player3 || Value == 0.0f) return;

	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	Player3->MoveInDirection(FVector(FVector::ForwardVector * Value), DeltaTime);
}
void APlayerInputManager::MoveLeftRightP3(float Value)
{
	if (!Player3 || Value == 0.0f) return;

	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	Player3->MoveInDirection(FVector(FVector::RightVector * Value), DeltaTime);
}
void APlayerInputManager::AttackP3()
{
	if (Player3) Player3->Attack();
}

/// <summary>
/// player 4 actions
/// </summary>
void APlayerInputManager::MoveUpDownP4(float Value)
{
	if (!Player4 || Value == 0.0f) return;

	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	Player4->MoveInDirection(FVector(FVector::ForwardVector * Value), DeltaTime);
}
void APlayerInputManager::MoveLeftRightP4(float Value)
{
	if (!Player4 || Value == 0.0f) return;

	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	Player4->MoveInDirection(FVector(FVector::RightVector * Value), DeltaTime);
}
void APlayerInputManager::AttackP4()
{
	if (Player4) Player4->Attack();
}