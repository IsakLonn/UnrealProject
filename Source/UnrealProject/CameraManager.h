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

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraBoom;

	USceneComponent* _FollowTarget;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//sets target for camera to follow
	//FollowDistance sets how far away to follow selected target
	//For example Followdistance 0 == FPS view
	void FollowTarget(USceneComponent* target, float FollowDistance);

	

};
