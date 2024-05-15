// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnController.h"

void UPawnController::SetUpVector(FVector Vector) { Up = Vector; }

void UPawnController::SetForwardVector(FVector Vector) { Forward = Vector; }

void UPawnController::SetRightVector(FVector Vector) { Right = Vector; }

FVector UPawnController::GetForwardVector() const { return Forward;}

FVector UPawnController::GetRightVector() const { return Right; }

FVector UPawnController::GetUpVector() const { return Up; }

void UPawnController::SetMovementInputX(float Value) { MovementInput.X = Value; }

void UPawnController::SetMovementInputY(float Value) { MovementInput.Y = Value; }

void UPawnController::SetMovementInputZ(float Value) { MovementInput.Z = Value; }

void UPawnController::SetMovementInput(FVector Input) { MovementInput = Input; }

void UPawnController::SetYawInput(float Value) { RotationInput.X = Value; }

void UPawnController::SetPitchInput(float Value) { RotationInput.Y = Value; }

void UPawnController::SetRotationInput(FVector2D Input) { RotationInput = Input; }

void UPawnController::SetIsJumping() { IsJumping = true;}

FVector2D UPawnController::ConsumeRotationInput()
{
	auto temp = RotationInput;
	RotationInput = {0,0};
	return temp;
}

FVector UPawnController::ConsumeMovementInput()
{
	auto temp = MovementInput;
	MovementInput = FVector::Zero();
	return temp;
}

bool UPawnController::ConsumeIsJumping()
{
	bool temp = IsJumping;
	IsJumping = false;
	return temp;
}

