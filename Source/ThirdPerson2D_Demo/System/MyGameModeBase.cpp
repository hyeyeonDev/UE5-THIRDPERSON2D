// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"
#include "MyGameInstance.h"
#include "MyPlayerController.h"
#include "MyPaperCharacter.h"


AMyGameModeBase::AMyGameModeBase()
{
    PlayerControllerClass = AMyPlayerController::StaticClass();
    DefaultPawnClass = AMyPaperCharacter::StaticClass();
}

void AMyGameModeBase::BeginPlay()
{
    Super::BeginPlay();
}

APawn* AMyGameModeBase::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
    APawn* NewPawn = Super::SpawnDefaultPawnFor_Implementation(NewPlayer, StartSpot);
    
    AMyPaperCharacter* MyCharacter = Cast<AMyPaperCharacter>(NewPawn);
    if (MyCharacter)
    {
        InitializeCharacter(MyCharacter);
    }

    return NewPawn;
}

void AMyGameModeBase::InitializeCharacter(AMyPaperCharacter* Character)
{
    if (Character)
    {
        UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
        if (GameInstance)
        {
            GameInstance->InitializeCharacterStats(Character, FName("Default"));
        }

        // 추가적인 캐릭터 초기화 로직을 여기에 구현
        // 예: 기본 아이템 지급, 시작 위치 설정 등
    }
}