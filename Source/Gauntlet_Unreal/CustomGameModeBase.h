// Fill out your copyright notice in the Description page of Project Settings.

/// <summary>
/// Devin G Monaghan 
/// 5/14/2025
/// Game Mode establishing no default pawn
/// </summary>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAUNTLET_UNREAL_API ACustomGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACustomGameModeBase();
};