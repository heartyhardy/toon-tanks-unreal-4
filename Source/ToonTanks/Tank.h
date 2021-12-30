// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	void HandleDestruction();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	APlayerController* GetPlayerController() const {return PlayerController;};

	bool IsAlive();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* ConnectorArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Speed = 100.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnSpeed = 50.f;

	APlayerController* PlayerController;

	bool bAlive = true;

	void Move(float Value);
	void Turn(float Value);
};
