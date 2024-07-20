// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();
    // InitializeEnemy();
    
    // OnActorBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnOverlapBegin);
}

// void AEnemyCharacter::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
// {
//     if (OtherActor && OtherActor != this)
//     {
//         APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
//         if (PlayerCharacter)
//         {
//             PlayerCharacter->TakeDamage(GetDamage());
//         }
//     }
// }

// void AEnemyCharacter::InitializeEnemy()
// {
//     if (EnemyDataTable)
//     {
//         FEnemyAttributes* AttributeRow = EnemyDataTable->FindRow<FEnemyAttributes>(EnemyID, TEXT(""));
//         if (AttributeRow)
//         {
//             CurrentAttributes = *AttributeRow;
            
//             // 속성에 따라 캐릭터 설정
//             GetCharacterMovement()->MaxWalkSpeed = CurrentAttributes.MovementSpeed;
//         }
//     }
// }