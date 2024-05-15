// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Core_PlayerCameraManager.h"

ACore_PlayerCameraManager::ACore_PlayerCameraManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	CameraRoot = CreateDefaultSubobject<USceneComponent>("CameraRoot");
	CameraRoot->SetupAttachment(RootComponent);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(CameraRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraBoom);
	
	StateManager = CreateDefaultSubobject<UCore_StateManager>("StateManager");
}

void ACore_PlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();
	SetViewTarget(this);
	CameraRoot->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	StateManager->InitStateManager();
}

void ACore_PlayerCameraManager::AttachToComponent(USceneComponent* Target) const { CameraRoot->AttachToComponent(Target, FAttachmentTransformRules::SnapToTargetNotIncludingScale); }

void ACore_PlayerCameraManager::SetTargetArmLength(float TargetArmLength) const { CameraBoom->TargetArmLength = TargetArmLength; }

USceneComponent* ACore_PlayerCameraManager::GetCameraRoot()
{
	return CameraRoot;
}

USpringArmComponent* ACore_PlayerCameraManager::GetCameraBoom()
{
	return CameraBoom;
}

// void ACore_PlayerCameraManager::CalculateMovement(float DeltatTime)
// {
// 	if(!bAllowMovement) return;
// 	
// 	auto CamPos = CameraRoot->GetRelativeLocation();
//
// 	FVector Forward = Controller->GetForwardVector();
// 	FVector Right = Controller->GetRightVector();
// 	FVector Up = Controller->GetUpVector();
// 	FVector MoveInput = Controller->ConsumeMovementInput();
// 		
// 	auto InputVelocity = ((Forward * MoveInput.X) + (Right * MoveInput.Y) + (Up * MoveInput.Z));
// 		
// 	CamPos += InputVelocity;
//
// 	CameraRoot->SetRelativeLocation(CamPos);
// }
