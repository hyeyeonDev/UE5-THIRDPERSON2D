#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EnemyEnums.generated.h"

UENUM(BlueprintType)
enum class EEnemyType : uint8
{
    Slime,
    Satiro,
};
