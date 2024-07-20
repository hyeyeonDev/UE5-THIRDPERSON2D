// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON2D_DEMO_API AEnemyCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	// UFUNCTION(BlueprintCallable, Category = "Enemy")
	// void InitializeEnemy();

	// UFUNCTION(BlueprintCallable, Category = "Enemy")
	// float GetDamage() const { return CurrentAttributes.Damage; }

protected:
	virtual void BeginPlay();
	
};
