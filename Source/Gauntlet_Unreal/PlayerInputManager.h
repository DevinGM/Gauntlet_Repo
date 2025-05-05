// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerParent.h"
#include "PlayerInputManager.generated.h"

UCLASS()
class GAUNTLET_UNREAL_API APlayerInputManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerInputManager();

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
	void SetupInputs(class UInputComponent* InputComp);

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