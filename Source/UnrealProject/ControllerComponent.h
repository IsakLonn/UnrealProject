// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ControllerComponent.generated.h"

//Custom Controller that keeps a vector and frotator value for pawn controlling
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API UControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UControllerComponent();

protected:
	FRotator ControllerRotation;
	FVector ControllerInput;
	FVector Forward;
	FVector Right;
	FVector Up;

public:	

	void SetUpDirection(FVector _Up);
	void SetForwardVector(FVector _Forward);
	void SetRightVector(FVector _Right);

	FVector GetForwardVector() const;
	FVector GetRightVector() const;

	void SetControllerInputX(float Value);
	void SetControllerInputY(float Value);
	void SetControllerInputZ(float Value);
	
	void SetControllerRotation(FRotator Rotation);
	void AddYawRotation(float Value);
	void AddPitchRotation(float Value);
	void AddRollRotation(float Value);

	FRotator GetControllerRotation() const;
	FVector GetControllerInput() const;
		
};
