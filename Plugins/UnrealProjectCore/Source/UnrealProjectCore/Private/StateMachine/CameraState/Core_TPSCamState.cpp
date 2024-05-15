// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/CameraState/Core_TPSCamState.h"

void UCore_TPSCamState::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	PlayerCameraManager->AttachToComponent(PossessedPawn->GetRootComponent());
	PlayerCameraManager->SetTargetArmLength(TargetArmLength);
}

void UCore_TPSCamState::OnRotation_Implementation(FVector2D Rotation)
{
	Super::OnRotation_Implementation(Rotation);

	auto CamYaw = PlayerCameraManager->GetCameraRoot()->GetRelativeRotation();
	auto CamPitch = PlayerCameraManager->GetCameraBoom()->GetRelativeRotation();
	
	//update rotations
	CamYaw.Yaw += Rotation.Y * RotationSpeed;
	
	CamPitch.Pitch += Rotation.X * RotationSpeed;
	CamPitch.Pitch = FMath::Clamp(CamPitch.Pitch, LookUpMin, LookUpMax);
	
	//set new rotations
	PlayerCameraManager->GetCameraRoot()->SetRelativeRotation(CamYaw);
	PlayerCameraManager->GetCameraBoom()->SetRelativeRotation(CamPitch);

	Controller->SetForwardVector(PlayerCameraManager->GetCameraRoot()->GetForwardVector());
	Controller->SetRightVector(PlayerCameraManager->GetCameraBoom()->GetRightVector());
}
