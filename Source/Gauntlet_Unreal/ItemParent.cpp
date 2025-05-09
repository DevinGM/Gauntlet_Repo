// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemTypes.h"
#include "ItemParent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerParent.h"

// Sets default values
AItemParent::AItemParent()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(50.f);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Overlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItemParent::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemParent::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (APlayerParent* Player = Cast<APlayerParent>(OtherActor))
	{
		Player->OnItemPickUp(ItemType);

		// Destroy item
		Destroy();
	}
}