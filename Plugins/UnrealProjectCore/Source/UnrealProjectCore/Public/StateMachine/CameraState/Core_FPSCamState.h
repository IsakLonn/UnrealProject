// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/CameraState/Core_CameraStateBase.h"
#include "Core_FPSCamState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECTCORE_API UCore_FPSCamState : public UCore_CameraStateBase
{
	GENERATED_BODY()

	virtual void OnRotation_Implementation(FVector2D Rotation) override;

	virtual void OnEnterState(AActor* StateOwner) override;

	UPROPERTY(EditAnywhere, Category="Rotation Settings", meta=(ClampMin="-89", ClampMax="-1"))
	float LookUpMin = -89;
	UPROPERTY(EditAnywhere, Category="Rotation Settings",meta=(ClampMin="0", ClampMax="89"))
	float LookUpMax = 89;
	UPROPERTY(EditAnywhere, Category="Rotation Settings",meta=(ClampMin="1", ClampMax="100"))
	float RotationSpeed = 1;
	
};
