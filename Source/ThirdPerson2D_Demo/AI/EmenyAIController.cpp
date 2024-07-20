// Fill out your copyright notice in the Description page of Project Settings.


#include "EmenyAIController.h"

AEmenyAIController::AEmenyAIController()
{
    // AI 인지 시스템 설정
    // SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
}

void AEmenyAIController::BeginPlay() 
{ 
    Super::BeginPlay();

    if(BehaviorTree)
    {
        RunBehaviorTree(BehaviorTree);
    }
}