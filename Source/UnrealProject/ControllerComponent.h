// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerComponentBase.h"
#include "Components/ActorComponent.h"
#include "ControllerComponent.generated.h"

//Custom Controller that keeps a vector and rotation value for pawn controlling
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API UControllerComponent : public UPlayerComponentBase
{
	
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	UControllerComponent();

	void SetUpVector(FVector _Up);
	void SetForwardVector(FVector _Forward);
	void SetRightVector(FVector _Right);

	FVector GetForwardVector() const;
	FVector GetRightVector() const;
	FVector GetUpVector() const;

	void SetMovementInputX(float Value);
	void SetMovementInputY(float Value);
	void SetMovementInputZ(float Value);
	
	void SetYawInput(float Value);
	void SetPitchInput(float Value);
	void SetRollInput(float Value);

	void SetIsJumping(bool Toggle);

	FVector ConsumeRotationInput();
	FVector ConsumeMovementInput();
	bool ConsumeIsJumping();
	
protected:
	
	FVector RotationInput;
	FVector MovementInput;
	FVector Forward;
	FVector Right;
	FVector Up;

	bool IsJumping;
	
};
