// Fill out your copyright notice in the Description page of Project Settings.


#include "CamControllerComponent.h"

// Sets default values for this component's properties
UCamControllerComponent::UCamControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCamControllerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UCamControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TryRotateCamera(DeltaTime);
	// ...
	
}

void UCamControllerComponent::Setup(USpringArmComponent* _CameraBoom, USceneComponent* _PlayerForwardRight)
{
	CameraBoom = _CameraBoom;
	PlayerForwardRight = _PlayerForwardRight;
	UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"), (CameraBoom != nullptr ? TEXT("true") : TEXT("false")));
	UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"), (PlayerForwardRight != nullptr ? TEXT("true") : TEXT("false")));
}

void UCamControllerComponent::SetRotationInputLR(float Value)
{
	RotationInput.Y = Value;
}

void UCamControllerComponent::SetRotationInputUD(float Value)
{
	RotationInput.X = Value;
}

void UCamControllerComponent::TryRotateCamera(float DeltaTime)
{
	if (CameraBoom == nullptr || PlayerForwardRight == nullptr) return;

	auto NewRotation = CameraBoom->GetRelativeRotation();

	NewRotation.Yaw += RotationInput.Y * CamRotSpeed * DeltaTime;
	NewRotation.Pitch += RotationInput.X * CamRotSpeed * DeltaTime;
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch, CameraUDMinPitch, CameraUDMaxPitch);

	CameraBoom->SetRelativeRotation(NewRotation);

	NewRotation.Pitch = 0;
	NewRotation.Roll = 0;

	PlayerForwardRight->SetRelativeRotation(NewRotation);

}

