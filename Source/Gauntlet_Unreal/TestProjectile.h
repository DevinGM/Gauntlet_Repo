// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestProjectile.generated.h"

UCLASS()
class GAUNTLET_UNREAL_API ATestProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UPROPERTY(VisibleAnywhere, EditAnywhere)
	//class UProjectileMovementComponent* ProjectileMovement;

	//UPROPERTY(VisibleAnywhere, EditAnywhere)
	//class USphereComponent* Collision;

	//UPROPERTY(VisibleAnywhere, EditAnywhere)
	//class UStaticMeshComponent* Mesh;

	//UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	//	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	//	const FHitResult& Hit);
};