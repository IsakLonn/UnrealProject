// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Core_PlayerController.h"

void ACore_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PossessedPawn = Cast<ACore_ControlledPawn>(InPawn);
}

ACore_PlayerController::ACore_PlayerController()
 {
	Controller = CreateDefaultSubobject<UCore_PawnController>("Controller");
 }

void ACore_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(MoveXAxisName, this, &ACore_PlayerController::MoveXAxis);
	InputComponent->BindAxis(MoveYAxisName, this, &ACore_PlayerController::MoveYAxis);
	InputComponent->BindAxis(MoveZAxisName, this, &ACore_PlayerController::MoveZAxis);
 	InputComponent->BindAxis(RotateYAxisName, this, &ACore_PlayerController::RotateYAxis);
 	InputComponent->BindAxis(RotateZAxisName, this, &ACore_PlayerController::RotateZAxis);
	InputComponent->BindAction(JumpKeyName, IE_Pressed,this, &ACore_PlayerController::Jump);
}

void ACore_PlayerController::SpawnPlayerCameraManager()
{
	PlayerCameraManagerClass = CustomPlayerCameraManager;
	Super::SpawnPlayerCameraManager();
	CameraManager = Cast<ACore_PlayerCameraManager>(PlayerCameraManager);
}

void ACore_PlayerController::MoveXAxis(float Value) { Controller->SetMovementInputX(Value); }

void ACore_PlayerController::MoveYAxis(float Value) { Controller->SetMovementInputY(Value); }

void ACore_PlayerController::MoveZAxis(float Value) { Controller->SetMovementInputZ(Value); }

void ACore_PlayerController::RotateZAxis(float Value) { Controller->SetYawInput(Value); }

void ACore_PlayerController::RotateYAxis(float Value) { Controller->SetPitchInput(Value); }

void ACore_PlayerController::Jump() { Controller->SendJumpDelegate(); }

ACore_ControlledPawn* ACore_PlayerController::GetPossessedPawn() const
{
	return PossessedPawn;
}

UCore_PawnController* ACore_PlayerController::GetPawnController() const
{
	return Controller;
}

ACore_PlayerCameraManager* ACore_PlayerController::GetPlayerCameraManager() const
{
	return CameraManager;
}

// void ACore_PlayerController::SetPerspective(Perspectives NewPerspective)
//  {
//  	auto ControllablePawn = Cast<AControllablePawnBase>(this->GetPawn());
//  	auto CameraManager = Cast<ACustomPlayerCameraManagerBase>(PlayerCameraManager);
//  	if (ControllablePawn && CameraManager) 
//  	{
//  		//allow rotations by default when changing perspective
//  		bBlockRotation = false;
// 	
//  		switch (NewPerspective)
//  		{
//  		case FPS:
//  			CameraManager->AttachToComponent(ControllablePawn->GetFPCamTarget());
//  			CameraManager->SetLocation(FVector::Zero(), false);
//  			CameraManager->SetTargetArmLength(0);
//  			//CamRotLRTarget = OrientationParent;
//  			//CamRotUDTarget = FPSCamTarget;
//  			break;
//
//  		case TPS:
//  			CameraManager->AttachToComponent(ControllablePawn->GetFPCamTarget());
//  			CameraManager->SetLocation(FVector::Zero(), false);
//  			CameraManager->SetTargetArmLength(300);
//  			//CamRotLRTarget = TPSCamTarget;
//  			//CamRotUDTarget = CamManager->GetCameraBoom();
//  			break;
//
//  		case TDW:
//  			CameraManager->AttachToComponent(ControllablePawn->GetRootComponent());
//  			CameraManager->SetLocation(FVector::UpVector * 1000, false);
//  			CameraManager->LookTowards(-ControllablePawn->GetActorUpVector());
//  			bBlockRotation = true;
//  			break;
//
//  		case SCW:
//  			bBlockRotation = true;
//  			break;
//  		}
//  	}
//  	
//  }
