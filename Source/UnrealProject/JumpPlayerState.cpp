// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpPlayerState.h"

void UJumpPlayerState::OnJumpInput()
{
	Super::OnJumpInput();
	PlayerRef->GetController()->SetIsJumping(true);
}

void UJumpPlayerState::OnMovementInput(FVector Input)
{
	Super::OnMovementInput(Input);
}

void UJumpPlayerState::TickState()
{
	Super::TickState();
	if(PlayerRef->GetMovement()->GetSettings()->bIsGrounded) PlayerRef->GetStateManager()->SwitchStateByKey("Idle");
}


