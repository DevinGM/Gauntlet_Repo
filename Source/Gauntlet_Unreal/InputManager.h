// Fill out your copyright notice in the Description page of Project Settings.

/// <summary>
/// Devin G Monaghan
/// 5/2/2025
/// Gets all player inputs and passes them to characters in the level
/// </summary>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerParent.h"
#include "InputManager.generated.h"

UCLASS()
class GAUNTLET_UNREAL_API AInputManager : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInputManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	APlayerParent* Player1;

	UPROPERTY(EditAnywhere)
	APlayerParent* Player2;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// player 1 actions
	UFUNCTION()
	void MoveUpDownP1(float Value);
	UFUNCTION()
	void MoveLeftRightP1(float Value);
	UFUNCTION()
	void AttackP1();

	// player 2 actions
	UFUNCTION()
	void MoveUpDownP2(float Value);
	UFUNCTION()
	void MoveLeftRightP2(float Value);
	UFUNCTION()
	void AttackP2();
};