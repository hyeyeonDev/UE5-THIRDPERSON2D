// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyPaperCharacter.h"
#include "MyPlayerController.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON2D_DEMO_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();

	virtual void BeginPlay() override;
    virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;

private:
    void InitializeCharacter(AMyPaperCharacter* Character);
};
