// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemTypes.h"
#include "ItemParent.h"
#include "Components/SphereComponent.h"
#include "PlayerParent.h"

// Sets default values
AItemParent::AItemParent()
{
	PrimaryActorTick.bCanEverTick = false;

	// create collision sphere
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(25.0f); // 25.0f is .5 in default sphere scale units
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void AItemParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// called when collision sphere detects overlap
void AItemParent::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// check if object collided with is a player
	if (APlayerParent* Player = Cast<APlayerParent>(OtherActor))
	{
		// call Player's item pick up logic according to current item
		Player->OnItemPickUp(ItemType);

		// Destroy item
		Destroy();
	}
}