// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletParent.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float Speed = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float LifeSpan = 2.0f;
	UPROPERTY(EditAnywhere)
	int Damage = 0;
	UPROPERTY(EditAnywhere)
	FVector Direction;
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionSphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	TSubclassOf<AActor> Enemy;

	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};