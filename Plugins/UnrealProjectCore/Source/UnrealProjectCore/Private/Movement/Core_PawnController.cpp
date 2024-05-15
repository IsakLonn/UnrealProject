// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/Core_PawnController.h"

UCore_PawnController::UCore_PawnController()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled	= true;
}

void UCore_PawnController::AddListener(ICore_IInputListener* InputListener)
{
	auto* obj = Cast<UObject>(InputListener);
	if(obj) { DelegatedInput.Add(obj, InputListener); }
}

void UCore_PawnController::RemoveListener(ICore_IInputListener* InputListener) { DelegatedInput.Remove(Cast<UObject>(InputListener)); }

void UCore_PawnController::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//calculate movement 
	FVector MovementDirection = ((Forward * MovementInput.X) + (Right * MovementInput.Y) + (Up * MovementInput.Z));

	for (auto Delegated : DelegatedInput)
	{
		Delegated.Value->Execute_OnMovement(Delegated.Key, MovementDirection);
		Delegated.Value->Execute_OnRotation(Delegated.Key, RotationInput);
	}

	//reset input for this frame
	MovementInput = FVector::Zero();
	RotationInput = FVector2D::Zero();
}

void UCore_PawnController::SetUpVector(FVector Vector) { Up = Vector; }

void UCore_PawnController::SetForwardVector(FVector Vector) { Forward = Vector; }

void UCore_PawnController::SetRightVector(FVector Vector) { Right = Vector; }

FVector UCore_PawnController::GetForwardVector() const { return Forward;}

FVector UCore_PawnController::GetRightVector() const { return Right; }

FVector UCore_PawnController::GetUpVector() const { return Up; }

void UCore_PawnController::SetMovementInputX(float Value) { MovementInput.X = Value; }

void UCore_PawnController::SetMovementInputY(float Value) { MovementInput.Y = Value; }

void UCore_PawnController::SetMovementInputZ(float Value) { MovementInput.Z = Value; }

void UCore_PawnController::SendJumpDelegate()
{
	
	for (auto Delegated : DelegatedInput)
	{
		Delegated.Value->Execute_OnJump(Delegated.Key);
	}
}

void UCore_PawnController::SetYawInput(float Value) { RotationInput.X = Value; }

void UCore_PawnController::SetPitchInput(float Value) { RotationInput.Y = Value; }

