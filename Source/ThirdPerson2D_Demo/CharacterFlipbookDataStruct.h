// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterEnums.h"
#include "CharacterFlipbookDataStruct.generated.h"

class UPaperFlipbook;

USTRUCT(BlueprintType)
struct THIRDPERSON2D_DEMO_API FCharacterFlipbookData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flipbook")
    ECharacterDirection Direction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flipbook")
    ECharacterState State;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flipbook")
    TSoftObjectPtr<UPaperFlipbook> Flipbook;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flipbook")
    float FramesPerSecond;

    FCharacterFlipbookData()
        : Direction(ECharacterDirection::Front)
        , State(ECharacterState::Idle)
        , FramesPerSecond(12.0f)
    {}
};