// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine/CameraState/Core_CameraStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/Core_PlayerController.h"

void UCore_CameraStateBase::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	if(const auto PlayerController = Cast<ACore_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		Controller = PlayerController->GetPawnController();
		PossessedPawn = PlayerController->GetPossessedPawn();
		PlayerCameraManager = PlayerController->GetPlayerCameraManager();

		if(Controller)
		{
			Controller->AddListener(this);
		}
	}
}

void UCore_CameraStateBase::OnMovement_Implementation(FVector Movement)
{
	if(!Controller || !PossessedPawn || !PlayerCameraManager) return;
	
	ICore_IInputListener::OnMovement_Implementation(Movement);

}

void UCore_CameraStateBase::OnRotation_Implementation(FVector2D Rotation)
{
	if(!Controller || !PossessedPawn || !PlayerCameraManager) return;
	
	ICore_IInputListener::OnRotation_Implementation(Rotation);

}


