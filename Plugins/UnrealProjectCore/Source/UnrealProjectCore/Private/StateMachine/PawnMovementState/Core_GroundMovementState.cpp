// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/PawnMovementState/Core_GroundMovementState.h"

void UCore_GroundMovementState::OnMovement_Implementation(FVector Movement)
{
	Super::OnMovement_Implementation(Movement);
	
	PlayerRef->GetMovementComponent()->AddMovement(Movement);

}

void UCore_GroundMovementState::OnJump_Implementation()
{
	Super::OnJump_Implementation();
	
	PlayerRef->GetMovementComponent()->Jump();
}
