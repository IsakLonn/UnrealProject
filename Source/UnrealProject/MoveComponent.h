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

	//setters for references
	
	void SetOrientation(USceneComponent* _Orientation);
	void SetController(UControllerComponent* _Controller);
	void SetCollider(UCapsuleComponent* _Collider);
	
	//setters for component variables

	
	void SetActorSpeed(float Speed);
	void ToggleGravity(bool Toggle);
	void SetOrientWithMovement(bool Toggle);
	void SetGravity(float _Gravity);
	
	void Jump();
	
protected:

	//References to other components
	
	//Reference to object that "looks" in move direction
	USceneComponent* Orientation;
	//Reference to Controller with information such as movement input
	UControllerComponent* Controller;
	//Reference to Collider
	UCapsuleComponent* Collider;
	
	bool bIsGrounded;

	float GravitationalMovement;

	void TryMovePawn(float DeltaTime);

	void OrientVisualsWithMovement();

	void GroundCheck();

	UPROPERTY(EditAnywhere, Category = "Movement settings")
	float ActorSpeed;
	UPROPERTY(EditAnywhere, Category = "Movement settings")
	float JumpStrength;

	UPROPERTY(EditAnywhere, Category = "Gravity settings")
	bool bUseGravity;
	UPROPERTY(EditAnywhere, Category = "Gravity settings")
	float Gravity;
	
	UPROPERTY(EditAnywhere, Category = "Visual settings")
	bool OrientWithMovement = true;
};
