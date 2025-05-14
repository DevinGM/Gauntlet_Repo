// Fill out your copyright notice in the Description page of Project Settings.

/// <summary>
/// Devin G Monaghan 
/// 5/14/2025
/// Handles door logic
/// </summary>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorParent.generated.h"

UCLASS()
class GAUNTLET_UNREAL_API ADoorParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// collision box
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;

	UFUNCTION()
	void NotifyActorBeginOverlap(AActor* OtherActor);
};