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

void UCamControllerComponent::SetComponentRotatedUD(USceneComponent* _ComponentRotatedUD)
{
	if (_ComponentRotatedUD == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("ComponentRotatedUD sent in to ComponentRotatedUD is null"));
		return;
	}
	ComponentRotatedUD = _ComponentRotatedUD;
}

void UCamControllerComponent::SetComponentRotatedLR(USceneComponent* _ComponentRotatedLR)
{
	if (_ComponentRotatedLR == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("ComponentRotatedLR sent in to SetComponentRotatedLR is null"));
		return;
	}
	ComponentRotatedLR = _ComponentRotatedLR;
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

void UCamControllerComponent::SetControllerComponent(UControllerComponent* _ControllerComponent)
{
	if(_ControllerComponent == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("ControllerComponent sent in to SetControllerComponent is null"));
		return;
	}
	ControllerComponent = _ControllerComponent;
}

void UCamControllerComponent::TryRotateCamera(float DeltaTime)
{
	if (ComponentRotatedLR == nullptr || ComponentRotatedUD == nullptr || ControllerComponent == nullptr) return;

	auto NewRotation = ControllerComponent->GetControllerRotation();

	auto ControllerRot = ControllerComponent->GetControllerRotation();
	auto UDRot = *new FRotator(ControllerRot.Pitch, 0, 0);
	auto LRRot = *new FRotator(0, ControllerRot.Yaw, 0);
	
	LRRot.Yaw *= CamRotSpeed;

	UDRot.Pitch *= CamRotSpeed;
	UDRot.Pitch = FMath::Clamp(NewRotation.Pitch, CameraUDMinPitch, CameraUDMaxPitch);

	UE_LOG(LogTemp, Warning, TEXT("The UDRot value is: %s"), *UDRot.ToString());
	UE_LOG(LogTemp, Warning, TEXT("The LRRot value is: %s"), *LRRot.ToString());
	
	ComponentRotatedLR->SetRelativeRotation(LRRot);
	ComponentRotatedUD->SetRelativeRotation(UDRot);
	ControllerComponent->SetControllerRotation(LRRot + UDRot);

	ControllerComponent->SetForwardVector(ComponentRotatedLR->GetForwardVector());
	ControllerComponent->SetRightVector(ComponentRotatedLR->GetRightVector());

}

