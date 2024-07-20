// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Enums/CharacterEnums.h"
#include "CharacterFlipbookManager.h"
#include "CharacterStatsDataStruct.h"
#include "MyPaperCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UPaperFlipbook;

UCLASS()
class THIRDPERSON2D_DEMO_API AMyPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()


public:
	AMyPaperCharacter();
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    void SetStats(const FCharacterStatsData& NewStats);

    UFUNCTION(BlueprintCallable, Category = "Character Stats")
    FCharacterStatsData GetCurrentStats() const { return CurrentStats; }

protected:
	virtual void BeginPlay();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State")
    ECharacterState CurrentState;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State")
    ECharacterDirection CurrentDirection;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fiplbook")
    UCharacterFlipbookManager* FlipbookManager;

    UPROPERTY(VisibleAnywhere, Category = "Character Stats")
    FCharacterStatsData CurrentStats;

private:
    void UpdateAnimation();
    void UpdateCharacterState();
    void LoadAnimations();

    // Camera boom to position the camera behind the character
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;

    // Follow camera
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;
};
