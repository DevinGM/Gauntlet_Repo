// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemParent.generated.h"

UCLASS()
class GAUNTLET_UNREAL_API AItemParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;

	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};