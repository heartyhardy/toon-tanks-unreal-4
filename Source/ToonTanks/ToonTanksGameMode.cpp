// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTankPlayerController.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    NumberOfTowers = GetTowerCount();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if(PlayerController)
    {
        PlayerController->SetPlayerEnabledState(false);
        
        FTimerHandle PlayerEnabledStateTimer;
        FTimerDelegate PlayerEnabledStateDelegate = FTimerDelegate::CreateUObject(
            PlayerController,
            &AToonTankPlayerController::SetPlayerEnabledState,
            true
        );
        
        GetWorldTimerManager().SetTimer(
            PlayerEnabledStateTimer,
            PlayerEnabledStateDelegate,
            StartDelay,
            false
        );
    }
}

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();

        if(PlayerController)
        {
            PlayerController->SetPlayerEnabledState(false);
        }

        EndGame(false);
    }
    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        
        NumberOfTowers > 1 ? --NumberOfTowers : EndGame(true);
    }
}

int32 AToonTanksGameMode::GetTowerCount()
{
    TArray<AActor*> Towers;

    UGameplayStatics::GetAllActorsOfClass(
        this,
        ATower::StaticClass(),
        Towers
    );

    return Towers.Num();
}