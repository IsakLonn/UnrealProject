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


void UControllerComponent::SetUpDirection(FVector _Up)
{
	Up = _Up;
}

void UControllerComponent::SetForwardVector(FVector _Forward)
{
	Forward = _Forward;
}

void UControllerComponent::SetRightVector(FVector _Right)
{
	Right = _Right;
}

FVector UControllerComponent::GetForwardVector() const
{
	return Forward;
}

FVector UControllerComponent::GetRightVector() const
{
	return Right;
}

void UControllerComponent::SetControllerInputX(float Value)
{
	ControllerInput.X = Value;
}

void UControllerComponent::SetControllerInputY(float Value)
{
	ControllerInput.Y = Value;
}

void UControllerComponent::SetControllerInputZ(float Value)
{
	ControllerInput.Z = Value;
}

void UControllerComponent::SetControllerRotation(FRotator Rotation)
{
	ControllerRotation = Rotation;
}

void UControllerComponent::AddYawRotation(float Value)
{
	ControllerRotation.Yaw += Value;
}

void UControllerComponent::AddPitchRotation(float Value)
{
	ControllerRotation.Pitch += Value;
}

void UControllerComponent::AddRollRotation(float Value)
{
	ControllerRotation.Roll += Value;
}

FRotator UControllerComponent::GetControllerRotation() const
{
	return ControllerRotation;
}

FVector UControllerComponent::GetControllerInput() const
{
	return ControllerInput;
}

