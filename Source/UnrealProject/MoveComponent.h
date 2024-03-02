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
	
	void SetOrientation(USceneComponent* NewOrientation);
	void SetController(UControllerComponent* NewController);
	void SetCollider(UCapsuleComponent* NewCollider);
	
	//setters for component variables
	
	void SetActorSpeed(float Speed);
	void ToggleGravity(const bool Toggle);
	void SetOrientWithMovement(const bool Toggle);
	void SetGravity(const float NewGravity);

	//makes actor jump
	void Jump();
	
protected:
	
	//Reference to object that "looks" in move direction
	UPROPERTY()
	USceneComponent* Orientation;
	//Reference to Controller with information such as movement input
	UPROPERTY()
	UControllerComponent* Controller;
	//Reference to Collider
	UPROPERTY()
	UCapsuleComponent* Collider;
	
	bool bIsGrounded;
	
	float GravitationalMovement;

	//tries to move actor according to input from controller
	void TryMoveActor(float DeltaTime);

	//orients visuals to face towards movement, without the Z value
	void OrientVisualsWithMovement() const;

	// checks if actor is on ground and sets bool values accordingly(bIsGrounded and bOnSlope)
	void GroundCheckTick();

	//snaps actor to ground if actor is grounded
	void SnapActorToGround();
	
	UPROPERTY(EditAnywhere, Category = "Movement settings")
	float ActorSpeed;
	UPROPERTY(EditAnywhere, Category = "Movement settings")
	float JumpStrength;

	UPROPERTY(EditAnywhere, Category = "Gravity settings")
	bool bUseGravity;
	UPROPERTY(EditAnywhere, Category = "Gravity settings")
	float Gravity;

	UPROPERTY(EditAnywhere,meta=(ClampMin="0", ClampMax="90"), Category = "Slope settings")
	float MaxSlopeAngle;
	
	UPROPERTY(EditAnywhere, Category = "Visual settings")
	bool OrientWithMovement = true;

	UPROPERTY(EditAnywhere, Category = "Debug settings")
	bool DebugGroundRayCast = true;
};
