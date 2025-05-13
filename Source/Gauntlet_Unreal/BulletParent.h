// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TimerManager.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletParent.generated.h"

// forward declaration
class APlayerParent;

UCLASS()
class GAUNTLET_UNREAL_API ABulletParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTimerHandle DestroyTimerHandle;

	// movement speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float Speed = 600.0f;
	// seconds before bullet automatically destroys itself
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float LifeSpan = 2.0f;
	// damage this bullet does to enemies, determined by player shooting
	UPROPERTY(EditAnywhere)
	int Damage = 0;
	// direction bullet moves in
	UPROPERTY(EditAnywhere)
	FVector Direction;
	// collision sphere
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionSphere;
	// reference to enemy class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	TSubclassOf<AActor> Enemy;
	// reference to player who spawned this bullet
	UPROPERTY(EditAnywhere)
	APlayerParent* Player;

	// called when bullet collision sphere detects overlap
	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	UFUNCTION()
	void SelfDestruct();
};