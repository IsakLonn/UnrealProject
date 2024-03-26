// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundMovementState.h"
#include "ControllerComponent.h"

void UGroundMovementState::EnterState()
{
	*GetMoveSettings() = GroundMovementSettings;
}

void UGroundMovementState::MovementInput(FVector Input)
{
	GetController()->SetMovementInputX(Input.X);
	GetController()->SetMovementInputY(Input.Y);
}

void UGroundMovementState::JumpInput()
{
	GetController()->SetIsJumping(true);
	ChangeMovementState.ExecuteIfBound(Jumping);
}

void UGroundMovementState::CrouchInput()
{
	
}


