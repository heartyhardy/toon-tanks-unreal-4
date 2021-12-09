// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATank::ATank()
{
    ConnectorArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Connector Arm"));
    ConnectorArm->SetupAttachment(RootComponent);

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
    FollowCamera->SetupAttachment(ConnectorArm);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
}

void ATank::Move(float Value)
{
    FVector DeltaOffset = FVector(0.f);
    DeltaOffset.X = Value;

    AddActorLocalOffset(DeltaOffset);
}