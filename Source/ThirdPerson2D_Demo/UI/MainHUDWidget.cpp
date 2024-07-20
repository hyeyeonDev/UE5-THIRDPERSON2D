// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDWidget.h"
#include "CharacterStatusWidget.h"
// #include "InventoryWidget.h"
// #include "SkillBarWidget.h"
#include "MyPaperCharacter.h"

UMainHUDWidget::UMainHUDWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    UE_LOG(LogTemp, Error, TEXT("MainHUDWidget"));
    StatusWidget = CreateDefaultSubobject<UCharacterStatusWidget>(TEXT("StatusWidget"));
}

void UMainHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (!StatusWidget)
    {
        UE_LOG(LogTemp, Error, TEXT("StatusWidget is null in NativeConstruct"));
        StatusWidget = Cast<UCharacterStatusWidget>(GetWidgetFromName(TEXT("StatusWidget")));
    }

    UpdateAllWidgets();
}

void UMainHUDWidget::SetCharacter(AMyPaperCharacter* InCharacter)
{
    if (this && InCharacter)
    {
        Character = InCharacter;
        UpdateAllWidgets();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid this pointer or InCharacter in SetCharacter"));
    }
}

void UMainHUDWidget::UpdateAllWidgets()
{

    if (!StatusWidget)
    {
        UE_LOG(LogTemp, Error, TEXT("StatusWidget is null in UpdateAllWidgets"));
        return;
    }

    if (!Character)
    {
        UE_LOG(LogTemp, Error, TEXT("Character is null in UpdateAllWidgets"));
        return;
    }

    StatusWidget->SetCharacter(Character);
    StatusWidget->UpdateStatus();

    UE_LOG(LogTemp, Warning, TEXT("UpdateAllWidgets completed successfully"));
    // if (InventoryWidget)
    // {
    //     InventoryWidget->UpdateInventory();
    // }

    // if (SkillBarWidget)
    // {
    //     SkillBarWidget->UpdateSkillBar();
    // }
}