// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "CameraManager.generated.h"

UCLASS()
class CONTROLLABEPAWN_API ACameraManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraManager();

	//attaches the camera to a new target
	//FollowDistance sets the target arm length for the spring arm
	void AttachToComponent(USceneComponent* Target) const;

	//returns the camera to the manager, i.e. reattaches the camera to the manager
	void ReturnCamera() const;

	void SetTargetArmLength(float TargetArmLength) const;

	//sets the offset from current target
	void SetTargetOffset(FVector offset);

	void SetFOV(float FOV) const;

	void Initiate();

	void LookTowards(FVector TargetLocation);

	USpringArmComponent* GetCameraBoom() const;
protected:

	UPROPERTY(EditAnywhere)
	USceneComponent* root;
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraBoom;
};
