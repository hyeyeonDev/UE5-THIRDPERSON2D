// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UEnhancedInputComponent;
class UInputMappingContext;
struct FInputActionValue;
class UInputAction;

UCLASS()
class THIRDPERSON2D_DEMO_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;


protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* RunAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* JumpAction;

private:
	class AMyPaperCharacter* MyCharacter;
    // class AMyPlayerCameraManager* CameraManager;

	// Functions to handle player input
    void Move(const FInputActionValue& Value);
    void StartRun(const FInputActionValue& Value);
    void StopRun(const FInputActionValue& Value);
    void StartJump();
    void StopJump();
    void Look(const FInputActionValue& Value);
};
