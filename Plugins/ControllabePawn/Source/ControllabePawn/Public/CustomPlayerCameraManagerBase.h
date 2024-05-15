// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "CustomPlayerCameraManagerBase.generated.h"

/**
 * 
 */
UCLASS()
class CONTROLLABEPAWN_API ACustomPlayerCameraManagerBase : public APlayerCameraManager
{
	GENERATED_BODY()

protected:
	ACustomPlayerCameraManagerBase();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> CameraRoot;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, meta=(ClampMin=-89, ClampMax = 0))
	float MinZRot;

	UPROPERTY(EditAnywhere, meta=(ClampMin=1, ClampMax = 89))
	float MaxZRot;

public:
	void AttachToComponent(USceneComponent* Target) const;

	void DeAttachCamera() const;

	void SetTargetArmLength(float TargetArmLength) const;
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	void SetLocation(FVector Location, bool bIsWorldLocation);
	void RotateZAxis(float Value);
	void RotateYAxis(float Value);
	void SetZRotClamp(float Min, float Max);
	void LookTowards(const FVector Vector);
	void CalculateMovement();
	void CalculateRotation();
};
