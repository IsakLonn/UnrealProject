// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerControllerBase.h"

#include "ControllablePawnBase.h"

 ACustomPlayerControllerBase::ACustomPlayerControllerBase()
 {
 	PlayerCameraManagerClass = CustomPlayerCameraManager;
 }

void ACustomPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
 	

	InputComponent->BindAxis(MoveXAxisName, this, &ACustomPlayerControllerBase::MoveXAxis);
	InputComponent->BindAxis(MoveYAxisName, this, &ACustomPlayerControllerBase::MoveYAxis);
	InputComponent->BindAxis(MoveZAxisName, this, &ACustomPlayerControllerBase::MoveZAxis);
 	InputComponent->BindAxis(RotateYAxisName, this, &ACustomPlayerControllerBase::RotateYAxis);
 	InputComponent->BindAxis(RotateZAxisName, this, &ACustomPlayerControllerBase::RotateZAxis);
}

void ACustomPlayerControllerBase::MoveXAxis(float Value)
{
	auto pawn = Cast<AControllablePawnBase>(this->GetPawn());
	if (pawn) 
	{
		pawn->GetPawnController()->SetMovementInputX(Value);
	}
}

void ACustomPlayerControllerBase::MoveYAxis(float Value)
{
	auto pawn = Cast<AControllablePawnBase>(this->GetPawn());
	if (pawn) 
	{
		pawn->GetPawnController()->SetMovementInputY(Value);
	}
}

void ACustomPlayerControllerBase::MoveZAxis(float Value)
{
	auto pawn = Cast<AControllablePawnBase>(this->GetPawn());
	if (pawn) 
	{
		pawn->GetPawnController()->SetMovementInputZ(Value);
	}
}

void ACustomPlayerControllerBase::RotateZAxis(float Value)
{
 	auto CamManager = Cast<ACustomPlayerCameraManagerBase>(PlayerCameraManager);
 	if(CamManager)
 	{
 		CamManager->RotateZAxis(Value);
 	}
}

void ACustomPlayerControllerBase::RotateYAxis(float Value)
{
 	auto CamManager = Cast<ACustomPlayerCameraManagerBase>(PlayerCameraManager);
 	if(CamManager)
 	{
 		CamManager->RotateYAxis(Value);
 	}
}

void ACustomPlayerControllerBase::SetPerspective(Perspectives NewPerspective)
 {
 	auto ControllablePawn = Cast<AControllablePawnBase>(this->GetPawn());
 	auto CameraManager = Cast<ACustomPlayerCameraManagerBase>(PlayerCameraManager);
 	if (ControllablePawn && CameraManager) 
 	{
 		//allow rotations by default when changing perspective
 		bBlockRotation = false;
	
 		switch (NewPerspective)
 		{
 		case FPS:
 			CameraManager->AttachToComponent(ControllablePawn->GetFPCamTarget());
 			CameraManager->SetLocation(FVector::Zero(), false);
 			CameraManager->SetTargetArmLength(0);
 			//CamRotLRTarget = OrientationParent;
 			//CamRotUDTarget = FPSCamTarget;
 			break;

 		case TPS:
 			CameraManager->AttachToComponent(ControllablePawn->GetFPCamTarget());
 			CameraManager->SetLocation(FVector::Zero(), false);
 			CameraManager->SetTargetArmLength(300);
 			//CamRotLRTarget = TPSCamTarget;
 			//CamRotUDTarget = CamManager->GetCameraBoom();
 			break;

 		case TDW:
 			CameraManager->AttachToComponent(ControllablePawn->GetRootComponent());
 			CameraManager->SetLocation(FVector::UpVector * 1000, false);
 			CameraManager->LookTowards(-ControllablePawn->GetActorUpVector());
 			bBlockRotation = true;
 			break;

 		case SCW:
 			bBlockRotation = true;
 			break;
 		}
 	}
 	
 }

void ACustomPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
 	
 	SetPerspective(TDW);
}


