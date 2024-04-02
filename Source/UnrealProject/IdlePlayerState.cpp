// Fill out your copyright notice in the Description page of Project Settings.


#include "IdlePlayerState.h"

void UIdlePlayerState::OnJumpInput()
{
	PlayerRef->GetController()->SetIsJumping(true);
	PlayerRef->GetStateManager()->SwitchStateByKey("Jump");
}

void UIdlePlayerState::OnMovementInput(FVector Input)
{
	PlayerRef->GetController()->SetMovementInputX(Input.X);
	PlayerRef->GetController()->SetMovementInputY(Input.Y);
}
