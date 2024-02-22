// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControllerComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MoveComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UMoveComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetOrientation(USceneComponent* _Orientation);
	void SetController(UControllerComponent* _Controller);

	//makes the mesh look where it is moving	
	//sets value for actors speed
	void SetActorSpeed(float speed);

	bool OrientWithMovement = true;
	
protected:

	//component for mesh, used for rotating
	USceneComponent* Orientation;
	//controller with information about directions of movement
	UControllerComponent* Controller;

	//starting rotation for visuals/mesh
	FRotator VisualsDefaultRotation;

	void TryMovePawn(float DeltaTime);

	void OrientVisualsWithMovement();

	UPROPERTY(EditAnywhere, Category = "Movement settings")
	float ActorSpeed;
};
