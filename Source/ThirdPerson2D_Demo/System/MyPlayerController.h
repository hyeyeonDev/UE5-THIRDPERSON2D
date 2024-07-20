// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UEnhancedInputComponent;
class UInputMappingContext;
struct FInputActionValue;
class UInputAction;
class AMainHUD;

UCLASS()
class THIRDPERSON2D_DEMO_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;

    UPROPERTY()
    AMainHUD* MainHUD;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> RunAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input,  meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> JumpAction;

    void CreateHUD();
    void UpdateHUD();
    TObjectPtr<UInputAction> LoadInputAction(const FString& Path);
    void InitializeCharacter();

private:
    class AMyPaperCharacter* MyCharacter;
    TSubclassOf<AMainHUD> MainHUDClass;
    // class AMyPlayerCameraManager* CameraManager;

	// Functions to handle player input
    void Move(const FInputActionValue& Value);
    void StartRun(const FInputActionValue& Value);
    void StopRun(const FInputActionValue& Value);
    void StartJump();
    void StopJump();
    void Look(const FInputActionValue& Value);
};
