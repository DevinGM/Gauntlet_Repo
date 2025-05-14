// Fill out your copyright notice in the Description page of Project Settings.

/// <summary>
/// Devin G Monaghan 
/// 5/14/2025
/// Parent bullet class
/// </summary>

#include "Components/SphereComponent.h"
#include "BulletParent.h"

// Sets default values
ABulletParent::ABulletParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create collision sphere
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(25.0f); // 25.0f is .5 in default sphere scale units
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Overlap);
}
      
// Called when the game starts or when spawned
void ABulletParent::BeginPlay()
{
	Super::BeginPlay();
	
	// set self destruct timer
	if (GetWorld())
		GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ABulletParent::SelfDestruct, 2.0f, false);
}

// Called every frame
void ABulletParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + Direction * Speed * DeltaTime;
	SetActorLocation(NewLocation);

}

void ABulletParent::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(Enemy))
	{
		//Enemy->Damage();
		//Enemy->health -= Damage;     /////////////////////////// PUT ENEMY DAMAGE CODE HERE
		/*
			if adding player score in bullet:
				- need to check if enemy is dead after damaging it
				- if so, add enemy's score to bullet's player
		
			if adding player score in enemy:
				- check for collision in enemy
				- take damage in enemy
				- upon death, add score to bullet's player		
		*/
	}

	// Destroy bullet
	if (!IsPendingKill())
		Destroy();
}

// destroy function for timer
void ABulletParent::SelfDestruct()
{
	if (!IsPendingKill())
		Destroy();
}