// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "MyPaperCharacter.h"
#include "MyPlayerCameraManager.h"
#include "Engine/LocalPlayer.h"
#include "MainHUD.h"


AMyPlayerController::AMyPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;

    // Load HUD Widget Class, Add "_C" !
    static ConstructorHelpers::FClassFinder<AMainHUD> MainHUDClassFinder(TEXT("'/Game/Blueprints/BP_MainHUD.BP_MainHUD_C'"));
    if (MainHUDClassFinder.Succeeded())
    {
        MainHUDClass = MainHUDClassFinder.Class;
    }

    // Load Input Mapping Context
    static ConstructorHelpers::FObjectFinder<UInputMappingContext> DefaultMappingContextObject(TEXT("'/Game/Input/IMC_Default.IMC_Default'"));
    DefaultMappingContext = DefaultMappingContextObject.Object;

    // Load Input Actions
    FString InputActionFolder = "'/Game/Input/Actions/";

    // Load Input Actions
    FString MoveActionPath = InputActionFolder + "IA_Move.IA_Move'";
    MoveAction = LoadInputAction(MoveActionPath); 

    FString RunActionPath = InputActionFolder + "IA_Run.IA_Run'";
    RunAction = LoadInputAction(RunActionPath); 

    FString JumpActionPath = InputActionFolder + "IA_Jump.IA_Jump'";
    JumpAction = LoadInputAction(JumpActionPath); 
}

TObjectPtr<UInputAction> AMyPlayerController::LoadInputAction(const FString& Path)
{
    // param: TObjectPtr<UInputAction>& Action
    // static ConstructorHelpers::FObjectFinder<UInputAction> ActionObject(*Path);
    // if (ActionObject.Succeeded())
    // {
    //     Action = ActionObject.Object;
    // }
    TObjectPtr<UInputAction> Action = LoadObject<UInputAction>(nullptr, *Path);
    if (!Action)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load InputAction at path: %s"), *Path);
    }
    return Action;
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
        EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AMyPlayerController::StartRun);
        EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AMyPlayerController::StopRun);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyPlayerController::StartJump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyPlayerController::StopJump);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get EnhancedInputComponent"));
    }
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    MyCharacter = Cast<AMyPaperCharacter>(GetPawn());

    // EnhancedInput
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }

    CreateHUD();
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    InitializeCharacter();
}

void AMyPlayerController::CreateHUD()
{
    if (MainHUDClass)
    {
        MainHUD = GetWorld()->SpawnActor<AMainHUD>(MainHUDClass);
        if (MainHUD)
        {
            MainHUD->SetOwner(this);
            InitializeCharacter();
            UpdateHUD();
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("MainHUDClass is not set"));
    }
}

void AMyPlayerController::UpdateHUD()
{
    if (MainHUD && MyCharacter)
    {
        MainHUD->SetCharacter(MyCharacter);
        MainHUD->UpdateAllWidgets();
    }
}

void AMyPlayerController::InitializeCharacter()
{
    // MyCharacter = Cast<AMyPaperCharacter>(GetPawn());
    if(!MyCharacter) 
    {   
        UE_LOG(LogTemp, Warning, TEXT("Failed to initialize character"));
    }

    if(!MainHUD)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to initialize HUD is not ready"));
    }

    if (MyCharacter && MainHUD)
    {
        MainHUD->SetCharacter(MyCharacter);
        UpdateHUD();
    }
}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
    if (MyCharacter) 
    {
        FVector2D MovementVector = Value.Get<FVector2D>();

        if (MyCharacter->Controller != nullptr) 
        {
            // find out which way is forward
            const FRotator Rotation = MyCharacter->Controller->GetControlRotation();
            const FRotator YawRotation(0, Rotation.Yaw, 0);

            // get forward vector : FVector(1.0f, 0.0f, 0.0f)
            const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

            // get right vector : FVector(0.0f, 1.0f, 0.0f)
            const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

            // add movement
            MyCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
            MyCharacter->AddMovementInput(RightDirection, MovementVector.X);
        }
    }
}

void AMyPlayerController::StartRun(const FInputActionValue& Value)
{
    if (MyCharacter)
    {
        float WalkSpeed = MyCharacter->GetCharacterMovement()->MaxWalkSpeed;
        MyCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
    }
}

void AMyPlayerController::StopRun(const FInputActionValue& Value)
{
    if (MyCharacter)
    {
        float WalkSpeed = MyCharacter->GetCharacterMovement()->MaxWalkSpeed;
        MyCharacter->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
    }
}

void AMyPlayerController::StartJump()
{
    if (MyCharacter)
    {
        MyCharacter->Jump();
    }
}

void AMyPlayerController::StopJump()
{
    if (MyCharacter)
    {
        MyCharacter->StopJumping();
    }
}

void AMyPlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (MyCharacter->Controller != nullptr)
	{
		// add yaw and pitch input to controller
		MyCharacter->AddControllerYawInput(LookAxisVector.X);
		MyCharacter->AddControllerPitchInput(LookAxisVector.Y);
	}
}
