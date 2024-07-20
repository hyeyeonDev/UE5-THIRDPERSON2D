// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
#include "MainHUDWidget.h"
#include "MyPaperCharacter.h"
#include "Blueprint/UserWidget.h"

AMainHUD::AMainHUD()
{
    static ConstructorHelpers::FClassFinder<UMainHUDWidget> MainHUDWidgetClassFinder(TEXT("'/Game/Blueprints/BP_MainHUDWidget.BP_MainHUDWidget'"));
    if (MainHUDWidgetClassFinder.Succeeded())
    {
        MainHUDWidgetClass = MainHUDWidgetClassFinder.Class;
    }
}

void AMainHUD::BeginPlay()
{
    Super::BeginPlay();
    CreateHUDWidget();
}

void AMainHUD::CreateHUDWidget()
{
    if (MainHUDWidgetClass)
    {
        MainHUDWidget = CreateWidget<UMainHUDWidget>(GetOwningPlayerController(), MainHUDWidgetClass);
        if (MainHUDWidget)
        {
            MainHUDWidget->AddToViewport();
        }
    }
}

void AMainHUD::UpdateAllWidgets()
{
    if (MainHUDWidget && Character)
    {
        MainHUDWidget->SetCharacter(Character);
        MainHUDWidget->UpdateAllWidgets();
    }
}

void AMainHUD::SetCharacter(AMyPaperCharacter* InCharacter)
{
    Character = InCharacter;
    UpdateAllWidgets();
}
