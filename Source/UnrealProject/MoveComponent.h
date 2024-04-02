// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControllerComponent.h"
#include "Structs.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MoveComponent.generated.h"

class APlayerPawn;
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

	FMoveSettings* GetSettings();

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

	//calculates velocity this frame
	void CalculateVelocity();
	
	// checks if actor is on ground and sets bool bIsGrounded accordingly
	void GroundCheck();

	//searches for an object below pawn and snaps it to stand on it
	void SnapActorToGround();

	//calculates and sets gravity value
	void CalculateGravity(float DeltaTime);

	//calculate and remove force
	void CalculateForce(float DeltaTime);

	APlayerPawn* GetPlayer() const;
	
	UPROPERTY(EditAnywhere, Category = "Movement settings")
	FMoveSettings Settings;
	
	//current force applied to the pawn
	FVector Force;
	FVector Velocity;

	
};
