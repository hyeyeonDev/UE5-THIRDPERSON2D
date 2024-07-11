// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPaperCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Engine/GameEngine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FlipbookManager.h"


AMyPaperCharacter::AMyPaperCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
    
    CurrentState = ECharacterState::Idle;
    CurrentDirection = ECharacterDirection::Front;

    GetCapsuleComponent()->InitCapsuleSize(8.0f, 5.0f);
    GetCapsuleComponent()->SetRelativeRotation(FRotator(0.0f, 00.0f, 0.0f));

    bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
    
    GetCharacterMovement()->bOrientRotationToMovement = false; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f);

    GetCharacterMovement()->JumpZVelocity = 400.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

    // Camera Setting
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 85.f;
	CameraBoom->SetRelativeRotation(FRotator(-15.f, -90.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	// CameraBoom->bUsePawnControlRotation = false;

    // Create the follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    ConstructorHelpers::FObjectFinder<UPaperFlipbook> FB_Idle(TEXT("PaperFlipbook'/Game/PaperAssets/Flipbook/FB_Idle_Front.FB_Idle_Front'"));
    if (FB_Idle.Succeeded())
    {
        GetSprite()->SetFlipbook(FB_Idle.Object);
    }
}

void AMyPaperCharacter::BeginPlay()
{
    Super::BeginPlay();

    FlipbookManager = NewObject<UFlipbookManager>();
    FlipbookManager->Initialize();
    if(GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("Hello")));
    }
}

void AMyPaperCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // UE_LOG(LogTemp, Error, TEXT("CurrentState: %d"), static_cast<int32>(CurrentState));
    // UE_LOG(LogTemp, Error, TEXT("CurrentDirection: %d"), static_cast<int32>(CurrentDirection));

    UpdateCharacterState();
    UpdateAnimation();
}

void AMyPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyPaperCharacter::UpdateCharacterState()
{
    FVector Velocity = GetVelocity();
    float SpeedX = FMath::Abs(Velocity.X);
    float SpeedY = FMath::Abs(Velocity.Y);
    float Speed = FMath::Sqrt(SpeedX * SpeedX + SpeedY * SpeedY);  // 전체 2D 속도

    const float RunningThreshold = 300.0f;
    static const float LandingThreshold = -200.0f;

    if (GetCharacterMovement()->IsFalling())
    {
        if(Velocity.Z < LandingThreshold)
        {
            CurrentState = ECharacterState::Falling;
        }
        else if(Velocity.Z > 0.0f)
        {
            CurrentState = ECharacterState::JumpRise;
        }
    }
    else if (Speed > RunningThreshold)
    {
        CurrentState = ECharacterState::Running;
    }
    else if (Speed > 0)
    {
        CurrentState = ECharacterState::Walking;
    }
    else
    {
        CurrentState = ECharacterState::Idle;
    }

    // 방향 결정
    if (Speed > 0)
    {
        if (SpeedX > SpeedY)
        {
            if (Velocity.X > 0)
            {
                CurrentDirection = ECharacterDirection::Right;
                UE_LOG(LogTemp, Error, TEXT("Right"));
            }
            else
            {
                CurrentDirection = ECharacterDirection::Left;
                UE_LOG(LogTemp, Error, TEXT("Left"));
            }
        }
        else
        {
            if (Velocity.Y > 0)
            {
                CurrentDirection = ECharacterDirection::Front;  // Y축 양의 방향이 앞쪽이라고 가정
                UE_LOG(LogTemp, Error, TEXT("Front"));
            }
            else
            {
                CurrentDirection = ECharacterDirection::Back;
                UE_LOG(LogTemp, Error, TEXT("Back"));
            }
        }
    }
}


void AMyPaperCharacter::UpdateAnimation()
{
    UPaperFlipbookComponent* FlipbookComponent = GetSprite();
    if (!FlipbookComponent) return;

    UPaperFlipbook* DesiredFlipbook = FlipbookManager->GetFlipbook(CurrentDirection, CurrentState);
    if (DesiredFlipbook && FlipbookComponent->GetFlipbook() != DesiredFlipbook)
    {
        FlipbookComponent->SetFlipbook(DesiredFlipbook);
    }

    // 캐릭터 회전 (옵션)
    // 참고: 2D 게임에서는 회전이 필요 없을 수 있으므로, 필요에 따라 주석 처리하거나 제거하세요.
    // SetActorRotation(FRotator(0, GetCharacterDirectionRotation(), 0));
}
