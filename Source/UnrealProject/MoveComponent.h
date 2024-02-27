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

	//bools for ground/slope checks
	
	bool bIsGrounded;
	bool bOnSlope;

	//raycast for ground/slope
	
	FHitResult* GroundRayCast = new FHitResult();
	FHitResult* SlopeRayCast = new FHitResult();

	float GravitationalMovement;

	//tries to move actor according to input from controller
	void TryMoveActor(float DeltaTime);

	//orients visuals to face towards movement, without the Z value
	void OrientVisualsWithMovement() const;

	// checks for ground and updates variables:
	// bOnSlope - bool for if actor is on a slope
	// bIsGrounded - bool for if actor is on the ground
	// GroundRayCast - FHitResult with ground information
	void RayCastGroundTick();
	
	UPROPERTY(EditAnywhere, Category = "Movement settings")
	float ActorSpeed;
	UPROPERTY(EditAnywhere, Category = "Movement settings")
	float JumpStrength;

	UPROPERTY(EditAnywhere, Category = "Gravity settings")
	bool bUseGravity;
	UPROPERTY(EditAnywhere, Category = "Gravity settings")
	float Gravity;

	UPROPERTY(EditAnywhere,meta=(ClampMin="0", ClampMax="60"), Category = "Slope settings")
	float MaxSlopeAngle;
	
	UPROPERTY(EditAnywhere, Category = "Visual settings")
	bool OrientWithMovement = true;

	UPROPERTY(EditAnywhere, Category = "Debug settings")
	bool DebugGroundRayCast = true;
};
