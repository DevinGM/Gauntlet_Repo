// Fill out your copyright notice in the Description page of Project Settings.

/// <summary>
/// Devin G Monaghan 
/// 5/14/2025
/// Handles input management
/// Instantiates HUD
/// </summary>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerParent.h"
#include "HUD_Parent.h"
#include "PlayerInputManager.generated.h"

class UUserWidget;

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

	// array of players in scene
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Players")
	TArray<AActor*> PlayerArray;

	// references to players
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Players")
	APlayerParent* Player1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Players")
	APlayerParent* Player2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Players")
	APlayerParent* Player3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Players")
	APlayerParent* Player4;
	
	// reference to hud
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> HUDClassRef;

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

	// player 3 actions
	UFUNCTION()
	void MoveUpDownP3(float Value);
	UFUNCTION()
	void MoveLeftRightP3(float Value);
	UFUNCTION()
	void AttackP3();

	// player 4 actions
	UFUNCTION()
	void MoveUpDownP4(float Value);
	UFUNCTION()
	void MoveLeftRightP4(float Value);
	UFUNCTION()
	void AttackP4();
};