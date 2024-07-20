#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "CharacterEnums.generated.h"

UENUM(BlueprintType)
enum class ECharacterDirection : uint8
{
    Front UMETA(DisplayName="Front"),
    Back UMETA(DisplayName="Back"),
    Left UMETA(DisplayName="Left"),
    Right UMETA(DisplayName="Right"),
};

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
    Idle UMETA(DisplayName="Idle"),
    Running UMETA(DisplayName="Running"),
    Walking UMETA(DisplayName="Walking"),
    JumpRise UMETA(DisplayName="JumpRise"),
    Falling UMETA(DisplayName="Falling"),
    Damage UMETA(DisplayName="Damage"),
    Death UMETA(DisplayName="Death"),
};