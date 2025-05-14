// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "DoorParent.h"
#include "PlayerParent.h"

// Sets default values
ADoorParent::ADoorParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create collision sphere
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetBoxExtent(FVector(100.f, 12.5f, 150.0f)); // 1 in blueprint transform = 50.0f
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void ADoorParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// called when collision sphere detects overlap
void ADoorParent::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// check if object collided with is a player
	if (APlayerParent* Player = Cast<APlayerParent>(OtherActor))
	{
		// if the player is holding any keys, destroy door
		if (Player->KeysHeld > 0)
		{
			Player->KeysHeld--;
			Destroy();
		}		
	}
}