// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "Movement/Core_PawnController.h"
#include "StateMachine/Core_StateManager.h"
#include "Core_PlayerCameraManager.generated.h"

UCLASS()
class UNREALPROJECTCORE_API ACore_PlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	ACore_PlayerCameraManager();
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> CameraRoot;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY()
	UCore_PawnController* Controller;

	UPROPERTY(EditAnywhere, Category="Camera Control States")
	UCore_StateManager* StateManager;

public:
	void AttachToComponent(USceneComponent* Target) const;

	void SetTargetArmLength(float TargetArmLength) const;

	USceneComponent* GetCameraRoot();
	USpringArmComponent* GetCameraBoom();
};
