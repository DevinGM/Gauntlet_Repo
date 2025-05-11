// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerParent.h"
#include "EngineUtils.h"
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
	
	// find all player characters
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

// Called every frame
void AMultiPlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// interpolate camera position to desired position
	FVector TargetPos = CalculateCenterPosition();
	FVector DesiredLocation = FVector(TargetPos.X - CameraXOffset, TargetPos.Y, CameraHeight);
	FVector NewLocation = FMath::VInterpTo(GetActorLocation(), DesiredLocation, DeltaTime, FollowSpeed);
	SetActorLocation(NewLocation);
}

// static function to allow player to access camera component
AMultiPlayerCamera* AMultiPlayerCamera::GetActiveCamera(UWorld* World)
{
	for (TActorIterator<AMultiPlayerCamera> It(World); It; ++It)
	{
		// Return the first (and supposedly only) one
		return *It; 
	}
	return nullptr;
}

// clamp player inside of viewport bounds
// only check when player is close to edge
FVector AMultiPlayerCamera::ClampWorldPositionToView(const FVector& WorldPosition, float Padding)
{
	if (!GEngine || !GEngine->GameViewport) return WorldPosition;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return WorldPosition;

	// Project world location to screen
	FVector2D ScreenPos;
	PC->ProjectWorldLocationToScreen(WorldPosition, ScreenPos);

	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	// Check if on screen within padding
	bool bOutOfBounds = false;
	if (ScreenPos.X < Padding || ScreenPos.X > ViewportSize.X - Padding ||
		ScreenPos.Y < Padding || ScreenPos.Y > ViewportSize.Y - Padding)
	{
		bOutOfBounds = true;
	}

	if (!bOutOfBounds)
	{
		// Already within view bounds — don't modify position
		return WorldPosition;
	}

	// Clamp screen position
	ScreenPos.X = FMath::Clamp(ScreenPos.X, Padding, ViewportSize.X - Padding);
	ScreenPos.Y = FMath::Clamp(ScreenPos.Y, Padding, ViewportSize.Y - Padding);

	// Convert back to world space
	FVector WorldLocation, WorldDirection;
	if (PC->DeprojectScreenPositionToWorld(ScreenPos.X, ScreenPos.Y, WorldLocation, WorldDirection))
	{
		float Distance = (WorldPosition.Z - WorldLocation.Z) / WorldDirection.Z;
		return WorldLocation + WorldDirection * Distance;
	}

	return WorldPosition;
}