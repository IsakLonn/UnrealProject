// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "CameraManager.generated.h"

UCLASS()
class UNREALPROJECT_API ACameraManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	USceneComponent* root;
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraBoom;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//attaches the camera to a new target
	//FollowDistance sets the target arm length for the spring arm
	void AttachToComponent(USceneComponent* Target, float TargetArmLength, bool SnapToTarget = true) const;

	//returns the camera to the manager, i.e. reattaches the camera to the manager
	void ReturnCamera() const;

	void SetLocation(FVector Location, bool bRelativeLocation) const;
	void SetRotation(FRotator Rotation, bool bRelativeRotation) const;

	void SetTargetArmLength(float TargetArmLength) const;

	void SetFOV(float FOV) const;

	
};
