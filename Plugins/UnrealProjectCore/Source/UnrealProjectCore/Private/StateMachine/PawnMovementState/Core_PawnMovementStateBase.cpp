// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/PawnMovementState/Core_PawnMovementStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Managers/Core_PlayerController.h"

void UCore_PawnMovementStateBase::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	if(const auto PlayerController = Cast<ACore_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		Controller = PlayerController->GetPawnController();
		UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"), ( Controller ? TEXT("true") : TEXT("false") ));
		if(Controller) { Controller->AddListener(this); }
	}
	PlayerRef = Cast<ACore_ControlledPawn>(StateOwner);
	
	if(PlayerRef)
	{
		PlayerRef->GetMovementComponent()->SetSettings(MovementStateSettings);
	}
}

void UCore_PawnMovementStateBase::OnExitState()
{
	
	Super::OnExitState();
	
	if(PlayerRef)
	{
		// PlayerRef->JumpDelegate.RemoveAll(this);
		// PlayerRef->MovementInputDelegate.RemoveAll(this);
	}
}

void UCore_PawnMovementStateBase::OnMovement_Implementation(FVector Movement)
{
	ICore_IInputListener::OnMovement_Implementation(Movement);
}

void UCore_PawnMovementStateBase::OnRotation_Implementation(FVector2D Rotation)
{
	ICore_IInputListener::OnRotation_Implementation(Rotation);
}

void UCore_PawnMovementStateBase::OnJump_Implementation()
{
	ICore_IInputListener::OnJump_Implementation();
}
