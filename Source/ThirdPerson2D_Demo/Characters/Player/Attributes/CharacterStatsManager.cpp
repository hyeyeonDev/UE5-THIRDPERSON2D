// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatsManager.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "CharacterStatsDataStruct.h"
#include "MyPaperCharacter.h"

UCharacterStatsManager::UCharacterStatsManager()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> DefaultDataTableObj(TEXT("/Script/Engine.DataTable'/Game/Data/DT_CharacterStats.DT_CharacterStats'"));
    if (DefaultDataTableObj.Succeeded())
    {
        StatsDataTable = DefaultDataTableObj.Object;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to find default StatsDataTable Please set it manually."));
    }

}

void UCharacterStatsManager::Initialize()
{
    LoadStatsToCache();
}

void UCharacterStatsManager::LoadStatsToCache()
{
    if (StatsDataTable.IsValid())
    {
        UDataTable* DataTable = StatsDataTable.LoadSynchronous();
        if (DataTable)
        {
            TArray<FName> RowNames = DataTable->GetRowNames();
            for (const FName& RowName : RowNames)
            {
                FCharacterStatsData* RowData = DataTable->FindRow<FCharacterStatsData>(RowName, TEXT(""));
                if (RowData)
                {
                    StatsCache.Add(RowName, *RowData);
                    // UE_LOG(LogTemp, Log, TEXT("Loaded RowName: %s"), *RowName.ToString());
                }
            }
        }
    }
}

void UCharacterStatsManager::InitializeCharacterStats(AMyPaperCharacter* Character, FName CharacterID)
{
    if (Character && StatsCache.Contains(CharacterID))
    {
        FCharacterStatsData Stats = StatsCache[CharacterID];
        Character->SetStats(Stats);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to initialize character stats for ID: %s"), *CharacterID.ToString());
    }
}

FCharacterStatsData* UCharacterStatsManager::GetCharacterStats(FName CharacterID)
{
     if (StatsCache.Contains(CharacterID))
    {
        return &StatsCache[CharacterID];
    }

    return nullptr;
}

bool UCharacterStatsManager::LevelUpCharacter(AMyPaperCharacter* Character, FName CharacterID)
{
    if (Character && StatsCache.Contains(CharacterID))
    {
        FCharacterStatsData& CurrentStats = StatsCache[CharacterID];
        CurrentStats.Level++;
        
        // 여기에서 레벨업에 따른 스탯 증가 로직을 구현합니다.
        CurrentStats.MaxHealth *= 1.1f; // 최대 체력 10% 증가

        Character->SetStats(CurrentStats);
        return true;
    }
    return false;
}