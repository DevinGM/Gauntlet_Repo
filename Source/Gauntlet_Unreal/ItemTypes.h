#pragma once

#include "CoreMinimal.h"
#include "ItemTypes.generated.h"

/// <summary>
/// Devin G Monaghan
/// 5/9/2025
/// Holds item type enum
/// </summary>

UENUM(BlueprintType)
enum class EItemType : uint8
{
    HealthPickup      UMETA(DisplayName = "Health Pickup"),
    ScorePickup        UMETA(DisplayName = "Score Pickup"),
    KeyPickup        UMETA(DisplayName = "Key Pickup"),
};