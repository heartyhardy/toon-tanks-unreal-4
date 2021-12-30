// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(Tank && Tank->IsAlive())
    {
        float Distance = GetDistanceToEnemy();

        if(IsEnemyInRange())
        {
            RotateTurret(Tank->GetActorLocation());
        }
    }
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    
    GetWorldTimerManager()
    .SetTimer(FireTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
    if(!Tank) return;

    if(IsEnemyInRange() && Tank->IsAlive())
    {
        Fire();
    }
}

float ATower::GetDistanceToEnemy()
{
    float Distance = FVector::Dist(
        GetActorLocation(),
        Tank->GetActorLocation()
    );
    return Distance;
}

bool ATower::IsEnemyInRange()
{
    return GetDistanceToEnemy() <= FireRange ? true : false;
}