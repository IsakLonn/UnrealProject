// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControllablePawnStructs.h"
#include "PawnController.h"
#include "GameFramework/PawnMovementComponent.h"
#include "ControllablePawnMovement.generated.h"

UCLASS()
class CONTROLLABEPAWN_API UControllablePawnMovement : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	
	FMoveSettingss* GetSettings();
	FVector GetVelocity();
	
	//adds force to the pawn
	UFUNCTION(BlueprintCallable)
	void AddForce(FVector Direction, float Strength);
	
	

protected:
	
	//tries to move actor according to input from controller
	void SimpleMove(float DeltaTime);

	//adds final movement after actor has been snapped correctly to the ground
	// calculates movement such as:
	// gravitational
	//force
	void FinalMove(float DeltaTime);
	
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

	UPawnController* GetOwnerController() const;
	
	UPROPERTY(EditAnywhere, Category = "Movement settings")
	FMoveSettingss Settings;
	
	FVector Force;
	FVector Velocity;
	float GravitationalMovement;
	
};
