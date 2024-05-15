// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/CameraState/Core_FPSCamState.h"

void UCore_FPSCamState::OnRotation_Implementation(FVector2D Rotation)
{
	Super::OnRotation_Implementation(Rotation);

	auto CamYaw = PossessedPawn->GetOrientationParent()->GetRelativeRotation();
	auto CamPitch = PlayerCameraManager->GetCameraRoot()->GetRelativeRotation();
	
	//update rotations
	CamYaw.Yaw += Rotation.Y * RotationSpeed;
	
	CamPitch.Pitch += Rotation.X * RotationSpeed;
	CamPitch.Pitch = FMath::Clamp(CamPitch.Pitch, LookUpMin, LookUpMax);
	
	//set new rotations
	PlayerCameraManager->GetCameraRoot()->SetRelativeRotation(CamPitch);
	PossessedPawn->GetOrientationParent()->SetRelativeRotation(CamYaw);

	Controller->SetForwardVector(PossessedPawn->GetOrientationParent()->GetForwardVector());
	Controller->SetRightVector(PlayerCameraManager->GetCameraRoot()->GetRightVector());
}

void UCore_FPSCamState::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	if(PlayerCameraManager)
	{
		PlayerCameraManager->AttachToComponent(PossessedPawn->GetOrientationParent());
		PlayerCameraManager->SetTargetArmLength(0);
	}
	
}
