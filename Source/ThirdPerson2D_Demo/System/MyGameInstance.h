// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CharacterStatsManager.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON2D_DEMO_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    virtual void Init() override;

    UFUNCTION(BlueprintCallable, Category = "Character Stats")
    UCharacterStatsManager* GetCharacterStatsManager() const { return CharacterStatsManager; }

    UFUNCTION(BlueprintCallable, Category = "Character")
    void InitializeCharacterStats(AMyPaperCharacter* Character, FName CharacterID);

private:
    UPROPERTY()
    UCharacterStatsManager* CharacterStatsManager;
};
