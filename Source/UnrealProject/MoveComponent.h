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
//Custom move component for moving an actor with a Capsule collider root. Make sure to set its updated component correctly
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

	//adds force to the pawn
	UFUNCTION(BlueprintCallable)
	void AddForce(FVector Direction, float Strength);
	
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
	void SimpleMove(float DeltaTime);

	//adds final movement after actor has been snapped correctly to the ground
	// calculates movement such as:
	// gravitational
	//force
	void FinalMove(float DeltaTime);

	//orients visuals to face towards movement, without the Z value
	void RotateTowardsMovement(float DeltaTime, float RotationSpeed) const;

	// checks if actor is on ground and sets bool bIsGrounded accordingly
	void GroundCheck();

	//searches for an object below pawn and snaps it to stand on it
	void SnapActorToGround();

	//calculates and sets gravity value
	void CalculateGravity(float DeltaTime);

	//calculate and remove force
	void CalculateForce(float DeltaTime);
	
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

	UPROPERTY(EditAnywhere, Category = "Force settings")
	float ForceDissipationPerFrame;

	UPROPERTY(EditAnywhere, Category = "Force settings")
	float MaxAppliedForce;

	//current force applied to the pawn
	FVector Force;
};
