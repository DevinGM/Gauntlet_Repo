// Fill out your copyright notice in the Description page of Project Settings.

/// <summary>
/// Devin G Monaghan 
/// 5/9/2025
/// Parent character class
/// </summary>

#pragma once

#include "ItemTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int maxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int currentHealth = maxHealth;
	UPROPERTY(EditAnywhere, Category = "Stats")
	int armor = 0;
	UPROPERTY(EditAnywhere, Category = "Stats")
	int score = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int damage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float moveSpeed = 600.0f;

	FVector LastMovementInput = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TSubclassOf<class AActor> Projectile;

	UFUNCTION(BlueprintCallable)
	void Attack();
	UFUNCTION(BlueprintCallable)
	void MoveUpDown(float Value);
	UFUNCTION(BlueprintCallable)
	void MoveLeftRight(float Value);
	UFUNCTION(BlueprintCallable)
	void Damage(int Amount);
	UFUNCTION(BlueprintCallable)
	void Heal(int Amount);
	UFUNCTION(BlueprintCallable)
	void AddScore(int Amount);
	UFUNCTION(BlueprintCallable)
	void OnItemPickUp(EItemType Item);
};