// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/CameraState/Core_CameraStateBase.h"
#include "Core_TPSCamState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECTCORE_API UCore_TPSCamState : public UCore_CameraStateBase
{
	GENERATED_BODY()

	virtual void OnEnterState(AActor* StateOwner) override;

	virtual void OnRotation_Implementation(FVector2D Rotation) override;

	UPROPERTY(EditAnywhere, Category="General Settings",meta=(ClampMin="100", ClampMax="1000"))
	float TargetArmLength = 1;

	UPROPERTY(EditAnywhere, Category="Rotation Settings",meta=(ClampMin="1", ClampMax="100"))
	float RotationSpeed = 1;
	UPROPERTY(EditAnywhere, Category="Rotation Settings", meta=(ClampMin="-89", ClampMax="-1"))
	float LookUpMin = -89;
	UPROPERTY(EditAnywhere, Category="Rotation Settings",meta=(ClampMin="0", ClampMax="89"))
	float LookUpMax = 89;
	
};
