// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SphereComponent.h"
#include "BulletParent.h"

// Sets default values
ABulletParent::ABulletParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(25.0f);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Overlap);

	// Auto-destroy after lifespan
	InitialLifeSpan = LifeSpan;
}

// Called when the game starts or when spawned
void ABulletParent::BeginPlay()
{
	Super::BeginPlay();
	
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
		//Enemy->health -= Damage;

		// Destroy bullet
		Destroy();
	}
}