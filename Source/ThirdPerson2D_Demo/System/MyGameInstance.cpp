// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "MyPaperCharacter.h"



void UMyGameInstance::Init() 
{ 
    Super::Init();
    CharacterStatsManager = NewObject<UCharacterStatsManager>(this);
    CharacterStatsManager->Initialize();
}

void UMyGameInstance::InitializeCharacterStats(AMyPaperCharacter* Character, FName CharacterID)
{
    if (CharacterStatsManager && Character)
    {
        CharacterStatsManager->InitializeCharacterStats(Character, CharacterID);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to initialize character stats. CharacterStatsManager or Character is null."));
    }
}