// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EmenyAIController.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON2D_DEMO_API AEmenyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEmenyAIController();

    virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = AI)
    class UBehaviorTree* BehaviorTree;
};
