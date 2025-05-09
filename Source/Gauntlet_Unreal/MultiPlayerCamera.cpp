// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerParent.h"
#include "MultiPlayerCamera.h"

// Sets default values
AMultiPlayerCamera::AMultiPlayerCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a dummy scene root
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// Create and attach the camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void AMultiPlayerCamera::BeginPlay()
{
	Super::BeginPlay();
	
	// Optionally find all player characters automatically
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerParent::StaticClass(), TrackedPlayers);

	// Set this camera as the view target
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		PC->SetViewTarget(this);
	}
}

FVector AMultiPlayerCamera::CalculateCenterPosition() const
{
	// if there are no players in the level, remain at 0,0,0
	if (TrackedPlayers.Num() == 0) return FVector::ZeroVector;

	FVector Sum = FVector::ZeroVector;
	for (AActor* Actor : TrackedPlayers)
	{
		if (Actor) Sum += Actor->GetActorLocation();
	}

	return Sum / TrackedPlayers.Num();
}

/*
* WIP code to clamp players to bounds of the camera
* 
// get the bounds of the camera and return as a bounding box
FBox AMultiPlayerCamera::GetCameraViewBounds() const
{
	if (!Camera) return FBox();

	FVector CameraLocation = Camera->GetComponentLocation();
	FRotator CameraRotation = Camera->GetComponentRotation();

	// Define the screen size in world space
	float HalfFOV = FMath::DegreesToRadians(Camera->FieldOfView / 2.0f);
	float AspectRatio = Camera->AspectRatio;
	float Distance = 1000.f; // How far ahead to check from the camera center

	float Height = 2.0f * Distance * FMath::Tan(HalfFOV);
	float Width = Height * AspectRatio;

	FVector Forward = Camera->GetForwardVector();
	FVector Center = CameraLocation + Forward * Distance;

	FVector Extents = FVector(Width / 2.f, Height / 2.f, 500.f); // Add Z buffer

	return FBox(Center - Extents, Center + Extents);
}

// clamp given player inside given bounding box
void AMultiPlayerCamera::ClampToCameraView(const FBox& CameraBounds, AActor* player)
{
	FVector CurrentLocation = player->GetActorLocation();
	FVector ClampedLocation = CurrentLocation;

	ClampedLocation.X = FMath::Clamp(CurrentLocation.X, CameraBounds.Min.X, CameraBounds.Max.X);
	ClampedLocation.Y = FMath::Clamp(CurrentLocation.Y, CameraBounds.Min.Y, CameraBounds.Max.Y);
	ClampedLocation.Z = FMath::Clamp(CurrentLocation.Z, CameraBounds.Min.Z, CameraBounds.Max.Z);

	player->SetActorLocation(ClampedLocation);
}*/

// Called every frame
void AMultiPlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// interpolate camera position to desired position
	FVector TargetPos = CalculateCenterPosition();
	FVector DesiredLocation = FVector(TargetPos.X - CameraXOffset, TargetPos.Y, CameraHeight);
	FVector NewLocation = FMath::VInterpTo(GetActorLocation(), DesiredLocation, DeltaTime, FollowSpeed);
	SetActorLocation(NewLocation);
	
	/*
	// clamp each player to the bounds of the camera
	for (AActor* player : TrackedPlayers)
	{
		ClampToCameraView(GetCameraViewBounds(), player);
	}*/
}