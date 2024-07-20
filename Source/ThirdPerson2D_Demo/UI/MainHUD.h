// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UMainHUDWidget;
class AMyPaperCharacter;

UCLASS()
class THIRDPERSON2D_DEMO_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
    AMainHUD();

	virtual void BeginPlay() override;

    void UpdateAllWidgets();
    void SetCharacter(AMyPaperCharacter* InCharacter);

    UPROPERTY()
    UMainHUDWidget* MainHUDWidget;

private:
    UPROPERTY()
    AMyPaperCharacter* Character;

    TSubclassOf<UMainHUDWidget> MainHUDWidgetClass;

    void CreateHUDWidget();
	
};
