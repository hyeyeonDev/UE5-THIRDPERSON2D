// Fill out your copyright notice in the Description page of Project Settings.


// CharacterStatusWidget.cpp
#include "CharacterStatusWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "MyPaperCharacter.h"

void UCharacterStatusWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    // 필요한 초기화 작업
}

void UCharacterStatusWidget::SetCharacter(AMyPaperCharacter* InCharacter)
{
    Character = InCharacter;
    UpdateStatus();
    UE_LOG(LogTemp, Warning, TEXT("Character set successfully in CharacterStatusWidget"));
}

void UCharacterStatusWidget::UpdateStatus()
{
    if (!Character)
    {
        return;
    }

    FCharacterStatsData Stats = Character->GetCurrentStats();

    if (LevelText)
    {
        LevelText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), Stats.Level)));
    }

    if (HealthBar)
    {
        
        float HealthPercent = Stats.CurrentHealth / Stats.MaxHealth;
        HealthBar->SetPercent(HealthPercent);
    }

    if (HealthText)
    {
        HealthText->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), Stats.CurrentHealth, Stats.MaxHealth)));
    }

    if (ExperienceBar)
    {
      float ExpPercent = Stats.Experience / Stats.ExperienceToNextLevel;
      ExperienceBar->SetPercent(ExpPercent);
    }

    if (ExperienceText)
    {
        ExperienceText->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), Stats.Experience, Stats.ExperienceToNextLevel)));
    }
}