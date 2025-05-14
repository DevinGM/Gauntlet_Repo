// Fill out your copyright notice in the Description page of Project Settings.

/// <summary>
/// Devin G Monaghan 
/// 5/14/2025
/// Parent character class
/// </summary>

#pragma once

#include "TimerManager.h"
#include "BulletParent.h"
#include "ItemTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MultiPlayerCamera.h"
#include "PlayerParent.generated.h"

UCLASS(BluePrintable)
class GAUNTLET_UNREAL_API APlayerParent : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// timer handle for health drain
	FTimerHandle HealthDrainTimer;
	// timer handle for damage cooldown
	FTimerHandle DamageCoolDownTimer;

	// max health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int maxHealth = 100;
	// current health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int currentHealth = maxHealth;
	// amount of damage player can block in a hit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int armor = 0;
	// current score
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int score = 0;
	// amount of damage player deals
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int damage = 10;
	// movement speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float moveSpeed = 500.0f;
	// how many keys this player is holding
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int KeysHeld = 0;
	// is the player currently on damage cooldown?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool OnDamageCooldown = false;
	// reference to character's bullet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TSubclassOf<class ABulletParent> BulletClass;

	// spawn a bullet in direction player is facing
	UFUNCTION(BlueprintCallable)
	void Attack();
	// move in given direction
	UFUNCTION(BlueprintCallable)
	void MoveInDirection(FVector Direction, float DeltaTime);
	// take given amount of damage
	UFUNCTION(BlueprintCallable)
	void DealDamageToPlayer(int Amount, bool TimerDamage);
	// heal given amount of damage
	UFUNCTION(BlueprintCallable)
	void Heal(int Amount);
	// add given amount to score
	UFUNCTION(BlueprintCallable)
	void AddScore(int Amount);
	// item pickup logic
	UFUNCTION(BlueprintCallable)
	void OnItemPickUp(EItemType Item);
	// health drain logic
	UFUNCTION(BlueprintCallable)
	void HealthDrain();
	// damage cooldown logic
	UFUNCTION(BlueprintCallable)
	void DamageCooldown();
};