// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterCustomizeDataStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct THIRDPERSON2D_DEMO_API FCharacterCustomizeDataStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<USkeletalMesh*> HairStyles;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UTexture2D*> EyeColors;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UTexture2D*> SkinColors;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<USkeletalMesh*> ClothingOptions;
	
};
