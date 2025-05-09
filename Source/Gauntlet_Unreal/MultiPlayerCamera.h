// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MultiPlayerCamera.generated.h"

UCLASS()
class GAUNTLET_UNREAL_API AMultiPlayerCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMultiPlayerCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Stats")
	TArray<AActor*> TrackedPlayers;

	UPROPERTY(EditAnywhere, Category = "Stats")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float CameraHeight = 1200.f;
	UPROPERTY(EditAnywhere, Category = "Stats")
	float CameraXOffset = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Stats")
	float FollowSpeed = 5.0f;

	UFUNCTION()
	FVector CalculateCenterPosition() const;
	/*
	UFUNCTION()
	FBox GetCameraViewBounds() const;
	UFUNCTION()
	void ClampToCameraView(const FBox& CameraBounds, AActor* player);*/
};