// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseState.h"

#include "ControllablePawnBase.h"

void UPlayerBaseState::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	
	PlayerRef = Cast<AControllablePawnBase>(StateOwner);
	
	if(PlayerRef)
	{
		// PlayerRef->JumpDelegate.AddUObject(this, &UPlayerBaseState::OnJumpInput);
		// PlayerRef->MovementInputDelegate.AddUObject(this, &UPlayerBaseState::OnMovementInput);
		// *PlayerRef->GetMovement()->GetSettings() = MovementStateSettings;
	}
}

void UPlayerBaseState::OnExitState()
{
	
	Super::OnExitState();
	
	if(PlayerRef)
	{
		// PlayerRef->JumpDelegate.RemoveAll(this);
		// PlayerRef->MovementInputDelegate.RemoveAll(this);
	}
}

void UPlayerBaseState::OnJumpInput()
{
	
}

void UPlayerBaseState::OnMovementInput(FVector Input)
{
}
