// CharacterStatusWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterStatusWidget.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class THIRDPERSON2D_DEMO_API UCharacterStatusWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetCharacter(class AMyPaperCharacter* InCharacter);
    void UpdateStatus();

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* LevelText;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthBar;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* ExperienceBar;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* HealthText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ExperienceText;

private:
    UPROPERTY()
    class AMyPaperCharacter* Character;
};