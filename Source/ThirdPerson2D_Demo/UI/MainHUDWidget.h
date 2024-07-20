// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CharacterStatusWidget.h"
#include "MainHUDWidget.generated.h"

class UCharacterStatusWidget;
class AMyPaperCharacter;

UCLASS()
class THIRDPERSON2D_DEMO_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UMainHUDWidget(const FObjectInitializer& ObjectInitializer);

    virtual void NativeConstruct() override;
    
    void UpdateAllWidgets();
    void SetCharacter(class AMyPaperCharacter* InCharacter);

    // UCharacterStatusWidget* GetStatusWidget() const { return StatusWidget; }
    
    UPROPERTY(meta = (BindWidget))
    class UCharacterStatusWidget* StatusWidget;

    // UPROPERTY(meta = (BindWidget))
    // UInventoryWidget* InventoryWidget;

    // UPROPERTY(meta = (BindWidget))
    // USkillBarWidget* SkillBarWidget;

protected:
    UPROPERTY()
    AMyPaperCharacter* Character;
};
