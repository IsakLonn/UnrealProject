// Fill out your copyright notice in the Description page of Project Settings.


#include "CamComponent.h"

// Sets default values for this component's properties
UCamComponent::UCamComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCamComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UCamComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TryRotateCamera(DeltaTime);
	// ...
	
}

void UCamComponent::Setup(USceneComponent* _CamLR, USceneComponent* _CamUD)
{
	CamUD = _CamUD;
	CamLR = _CamLR;
	UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"), (CamLR != nullptr ? TEXT("true") : TEXT("false")));
	UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"), (CamUD != nullptr ? TEXT("true") : TEXT("false")));
}

void UCamComponent::SetRotationInputLR(float Value)
{
	RotationInput.Y = Value;
}

void UCamComponent::SetRotationInputUD(float Value)
{
	RotationInput.X = Value;
}

void UCamComponent::TryRotateCamera(float DeltaTime)
{
	if (CamUD == nullptr || CamLR == nullptr) return;

	auto LRRot = CamLR->GetRelativeRotation();
	auto UDRot = CamUD->GetRelativeRotation();

	LRRot.Yaw += RotationInput.Y * CamRotSpeed * DeltaTime;
	UDRot.Pitch += RotationInput.X * CamRotSpeed * DeltaTime;
	UDRot.Pitch = FMath::Clamp(UDRot.Pitch, CameraUDMinPitch, CameraUDMaxPitch);

	CamLR->SetRelativeRotation(LRRot);
	CamUD->SetRelativeRotation(UDRot);

	UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *CamUD->GetRelativeRotation().ToString());
}

