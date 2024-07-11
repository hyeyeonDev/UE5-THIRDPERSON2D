// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "CharacterEnums.h"
#include "FlipbookManager.generated.h"

class UPaperFlipbook;

UCLASS()
class THIRDPERSON2D_DEMO_API UFlipbookManager : public UObject
{
	GENERATED_BODY()

public:
    UFlipbookManager();

    UPROPERTY(EditDefaultsOnly, Category = "Flipbook")
    TSoftObjectPtr<UDataTable> FlipbookDataTable;

    UPROPERTY()
    TMap<FName, UPaperFlipbook*> FlipbookCache;

    void Initialize();
    UPaperFlipbook* GetFlipbook(ECharacterDirection Direction, ECharacterState State);

private:
    FName GenerateFlipbookKey(ECharacterDirection Direction, ECharacterState State);
};
