// Fill out your copyright notice in the Description page of Project Settings.

/// <summary>
/// Devin G Monaghan 
/// 5/14/2025
/// Holds HUD's variables
/// </summary>

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD_Parent.generated.h"

class APlayerInputManager;

/**
 * 
 */
UCLASS()
class GAUNTLET_UNREAL_API UHUD_Parent : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	APlayerInputManager* InputManagerReference;
};