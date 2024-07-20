// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterStatsDataStruct.generated.h"

USTRUCT(BlueprintType)
struct THIRDPERSON2D_DEMO_API FCharacterStatsData : public FTableRowBase
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
    int32 Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
    float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
    float CurrentHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
    float AttackPower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
    float DefensePower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
    float Experience;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
    float ExperienceToNextLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
    float MovementSpeed;

    FCharacterStatsData()
        : Level(1)
        , MaxHealth(100.0f)
        , CurrentHealth(100.0f)
        , AttackPower(10.0f)
        , DefensePower(5.0f)
        , Experience(0.0f)
        , ExperienceToNextLevel(100.0f)
        , MovementSpeed(300.0f)
    {}
};
