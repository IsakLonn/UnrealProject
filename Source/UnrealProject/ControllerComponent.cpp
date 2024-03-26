// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerComponent.h"

// Sets default values for this component's properties
UControllerComponent::UControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UControllerComponent::SetUpVector(FVector _Up) { Up = _Up; }

void UControllerComponent::SetForwardVector(FVector _Forward) { Forward = _Forward; }

void UControllerComponent::SetRightVector(FVector _Right) { Right = _Right; }

FVector UControllerComponent::GetForwardVector() const { return Forward; }

FVector UControllerComponent::GetRightVector() const { return Right; }

FVector UControllerComponent::GetUpVector() const { return Up;}

void UControllerComponent::SetMovementInputX(float Value) { MovementInput.X = Value; }

void UControllerComponent::SetMovementInputY(float Value) { MovementInput.Y = Value; }

void UControllerComponent::SetMovementInputZ(float Value) { MovementInput.Z = Value; }

void UControllerComponent::SetYawInput(float Value) { RotationInput.X = Value; }

void UControllerComponent::SetPitchInput(float Value) { RotationInput.Y = Value; }

void UControllerComponent::SetRollInput(float Value) { RotationInput.Z = Value; }

void UControllerComponent::SetIsJumping(bool Toggle) { IsJumping = Toggle;}

FVector UControllerComponent::ConsumeRotationInput()
{
	auto temp = RotationInput;
	RotationInput = {0,0,0};
	return temp;
}

FVector UControllerComponent::ConsumeMovementInput()
{
	auto temp = MovementInput;
	MovementInput = FVector::Zero();
	return temp;
}

bool UControllerComponent::ConsumeIsJumping()
{
	bool temp = IsJumping;
	IsJumping = false;
	return temp;
}

