// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCameraManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AMyPlayerCameraManager::AMyPlayerCameraManager()
{
    PrimaryActorTick.bCanEverTick = true;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->SetUsingAbsoluteRotation(true);
    CameraBoom->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	CameraBoom->TargetArmLength = 150.0f;
	CameraBoom->bUsePawnControlRotation = false;

    // Create the follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
    FollowCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
    FollowCamera->SetOrthoWidth(600.0f);
}

void AMyPlayerCameraManager::BeginPlay()
{
    Super::BeginPlay();
}

void AMyPlayerCameraManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyPlayerCameraManager::AttachCameraToTarget(APawn* Target)
{
    if (Target)
    {
        CameraBoom->SetupAttachment(Target->GetRootComponent());
    }
}