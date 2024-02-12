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

void UCamControllerComponent::Setup(USceneComponent* _RotatedComponent, USceneComponent* _DirectionalComponent, UCameraComponent* _Camera)
{
	SetCamera(_Camera);
	SetRotatedComponent(_RotatedComponent);
	SetDirectionalComponent(_DirectionalComponent);
}

void UCamControllerComponent::SetRotationInputLR(float Value)
{
	RotationInput.Y = Value;
}

void UCamControllerComponent::SetRotationInputUD(float Value)
{
	RotationInput.X = Value;
}

void UCamControllerComponent::SetRotatedComponent(USceneComponent* _RotatedComponent)
{
	if (_RotatedComponent == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("CameraParent sent in to SetCameraParent is null"));
		return;
	}
	RotatedComponent = _RotatedComponent;
}

void UCamControllerComponent::SetDirectionalComponent(USceneComponent* _DirectionalComponent)
{
	if (_DirectionalComponent == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("DirectionalComponent sent in to SetDirectionalComponent is null"));
		return;
	}
	DirectionalComponent = _DirectionalComponent;
}

void UCamControllerComponent::SetCamera(UCameraComponent* _Camera)
{
	if (_Camera == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Camera sent in to SetCamera is null"));
		return;
	}
	Camera = _Camera;
}

void UCamControllerComponent::TryRotateCamera(float DeltaTime)
{
	if (RotatedComponent == nullptr || DirectionalComponent == nullptr) return;

	auto NewRotation = RotatedComponent->GetRelativeRotation();

	if(bCanRotateLR)NewRotation.Yaw += RotationInput.Y * CamRotSpeed * DeltaTime;
	if(bCanRotateUD)NewRotation.Pitch += RotationInput.X * CamRotSpeed * DeltaTime;
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch, CameraUDMinPitch, CameraUDMaxPitch);

	RotatedComponent->SetRelativeRotation(NewRotation);

	NewRotation.Pitch = 0;
	NewRotation.Roll = 0;

	DirectionalComponent->SetRelativeRotation(NewRotation);

}

