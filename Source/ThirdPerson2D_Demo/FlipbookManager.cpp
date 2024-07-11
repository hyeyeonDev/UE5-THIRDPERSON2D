// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipbookManager.h"
#include "Engine/DataTable.h"
#include "PaperFlipbook.h"
#include "UObject/ConstructorHelpers.h"
#include "CharacterFlipbookDataStruct.h"

UFlipbookManager::UFlipbookManager()
{
    // 데이터 테이블의 기본 경로 설정
    static ConstructorHelpers::FObjectFinder<UDataTable> DefaultDataTableObj(TEXT("/Game/Data/DT_CharacterFlipbooks"));
    if (DefaultDataTableObj.Succeeded())
    {
        FlipbookDataTable = DefaultDataTableObj.Object;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to find default FlipbookDataTable. Please set it manually."));
    }

    // 기타 초기화 작업
    FlipbookCache.Empty();
}

void UFlipbookManager::Initialize()
{
    if (FlipbookDataTable.IsValid())
    {
        UDataTable* DataTable = FlipbookDataTable.LoadSynchronous();
        if (DataTable)
        {
            TArray<FCharacterFlipbookData*> FlipbookDatas;
            DataTable->GetAllRows<FCharacterFlipbookData>("", FlipbookDatas);

            for (const FCharacterFlipbookData* Data : FlipbookDatas)
            {
                if (Data)
                {
                    FName Key = GenerateFlipbookKey(Data->Direction, Data->State);
                    FlipbookCache.Add(Key, nullptr);  // 초기에는 nullptr로 설정
                }
            }
        }
    }
}

UPaperFlipbook* UFlipbookManager::GetFlipbook(ECharacterDirection Direction, ECharacterState State)
{
    FName Key = GenerateFlipbookKey(Direction, State);
    UPaperFlipbook** FoundFlipbook = FlipbookCache.Find(Key);

    if (FoundFlipbook)
    {
        if (*FoundFlipbook == nullptr)
        {
            // 플립북이 아직 로드되지 않았다면 로드합니다
            UDataTable* DataTable = FlipbookDataTable.LoadSynchronous();
            FCharacterFlipbookData* FlipbookData = DataTable->FindRow<FCharacterFlipbookData>(Key, TEXT(""));
            if (FlipbookData)
            {
                *FoundFlipbook = FlipbookData->Flipbook.LoadSynchronous();
            }
        }
        return *FoundFlipbook;
    }

    return nullptr;
}

FName UFlipbookManager::GenerateFlipbookKey(ECharacterDirection Direction, ECharacterState State)
{
    return FName(*FString::Printf(TEXT("%d_%d"), static_cast<int32>(Direction), static_cast<int32>(State)));
}