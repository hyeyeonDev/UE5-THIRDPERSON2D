// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "CharacterStatsDataStruct.h"
#include "CharacterStatsManager.generated.h"

class AMyPaperCharacter;

UCLASS()
class THIRDPERSON2D_DEMO_API UCharacterStatsManager : public UObject
{
	GENERATED_BODY()
	
public:
	UCharacterStatsManager();

	void Initialize();
	void InitializeCharacterStats(AMyPaperCharacter* Character, FName CharacterID);
    FCharacterStatsData* GetCharacterStats(FName CharacterID);

	bool LevelUpCharacter(AMyPaperCharacter* Character, FName CharacterID);

private:
    void LoadStatsToCache();

	UPROPERTY(EditDefaultsOnly, Category = "Character Stats")
	TSoftObjectPtr<UDataTable> StatsDataTable;

    TMap<FName, FCharacterStatsData> StatsCache;
};
