// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "MyPaperCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
    PlayerControllerClass = AMyPlayerController::StaticClass();
    DefaultPawnClass = AMyPaperCharacter::StaticClass();
}