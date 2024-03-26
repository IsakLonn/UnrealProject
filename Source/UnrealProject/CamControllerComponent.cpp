// Fill out your copyright notice in the Description page of Project Settings.


#include "CamControllerComponent.h"

// Sets default values for this component's properties
UCamControllerComponent::UCamControllerComponent(): ComponentRotatedUD(nullptr), ComponentRotatedLR(nullptr),
                                                    Controller(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UCamControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TryRotateComponents();
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

void UCamControllerComponent::SetController(UControllerComponent* _Controller)
{
	if(_Controller == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Controller sent in to SetController is null"));
		return;
	}
	Controller = _Controller;
}

void UCamControllerComponent::TryRotateComponents()
{
	//check for nullptr references
	if (ComponentRotatedLR == nullptr || ComponentRotatedUD == nullptr || Controller == nullptr) return;

	//get current rotations and inputs
	const auto RotationInput = Controller->ConsumeRotationInput();
	auto UDRot = ComponentRotatedUD->GetRelativeRotation();
	auto LRRot = ComponentRotatedLR->GetRelativeRotation();

	//update rotations
	LRRot.Yaw += RotationInput.X * YawSpeed;
	UDRot.Pitch += RotationInput.Y *  PitchSpeed;
	UDRot.Pitch = FMath::Clamp(UDRot.Pitch, CameraUDMinPitch, CameraUDMaxPitch);

	//set new rotations
	ComponentRotatedLR->SetRelativeRotation(LRRot);
	ComponentRotatedUD->SetRelativeRotation(UDRot);

	//set vectors that will be used to move actor
	Controller->SetForwardVector(ComponentRotatedLR->GetForwardVector());
	Controller->SetRightVector(ComponentRotatedLR->GetRightVector());
	Controller->SetUpVector(ComponentRotatedLR->GetUpVector());

}

