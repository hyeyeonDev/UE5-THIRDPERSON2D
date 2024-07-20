// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyEnums.h"
#include "EnemyAttributesDataStruct.generated.h"

class UBehaviorTree;
class UTexture2D;

USTRUCT(BlueprintType)
struct THIRDPERSON2D_DEMO_API FEnemyAttributesDataStruct : public FTableRowBase
{
	GENERATED_BODY()

    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    // EEnemyType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    float MovementSpeed;
};
