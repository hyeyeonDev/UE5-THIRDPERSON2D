// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "PaperCharacter.h"
#include "MyPaperCharacter.h"
#include "MyPlayerCameraManager.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyPlayerController::AMyPlayerController()
{
    UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController"));

    FString InputFolder = TEXT("/Script/EnhancedInput.InputAction'/Game/Input");
    // Load Input Mapping Context
    static ConstructorHelpers::FObjectFinder<UInputMappingContext> DefaultMappingContextObject(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
    if (DefaultMappingContextObject.Succeeded())
    {
        DefaultMappingContext = DefaultMappingContextObject.Object;
    }

    FString InputActionFolder = "/Script/EnhancedInput.InputAction'/Game/Input/Actions/";

    // Load Input Actions
    FString MoveActionPath = InputActionFolder + "IA_Move.IA_Move'";
    static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionObject(*MoveActionPath);
    if (MoveActionObject.Succeeded())
    {
        MoveAction = MoveActionObject.Object;
    }

    FString RunActionPath = InputActionFolder + "IA_Run.IA_Run'";
    static ConstructorHelpers::FObjectFinder<UInputAction> RunActionObject(*RunActionPath);
    if (MoveActionObject.Succeeded())
    {
        RunAction = RunActionObject.Object;
    }

    FString JumpActionPath = InputActionFolder + "IA_Jump.IA_Jump'";
    static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionObject(*JumpActionPath);
    if (JumpActionObject.Succeeded())
    {
        JumpAction = JumpActionObject.Object;
    }
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UE_LOG(LogTemp, Warning, TEXT("SetupInputComponent called"));

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

    // EnhancedInput
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }

    // MyCharacter
    MyCharacter = Cast<AMyPaperCharacter>(GetPawn());
    // if(MyCharacter)
    // {
    //     // Spawn the camera manager
    //     FActorSpawnParameters SpawnParameters;
    //     SpawnParameters.Owner = this;
    //     CameraManager = GetWorld()->SpawnActor<AMyPlayerCameraManager>(AMyPlayerCameraManager::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
    //     CameraManager->AttachCameraToTarget(MyCharacter);
    // }

    // Get the player character
    // AMyPaperCharacter* MyCharacter = Cast<AMyPaperCharacter>(GetPawn());
    // if (MyCharacter)
    // {
    //     // Get the capsule component (collision component)
    //     UCapsuleComponent* CapsuleComponent = MyCharacter->GetCapsuleComponent();
    //     if (CapsuleComponent)
    //     {
    //         // Bind the overlap event to the function
    //         CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayerController::OnPlayerOverlapBegin);
    //     }
    // }
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