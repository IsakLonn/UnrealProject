// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/Core_Structs.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Core_PawnMovement.generated.h"

UCLASS()
class UNREALPROJECTCORE_API UCore_PawnMovement : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	
	//adds force to the pawn
	UFUNCTION(BlueprintCallable)
	void AddForce(FVector Direction, float Strength);

	UFUNCTION(BlueprintCallable)
	void AddMovement(FVector Direction);

	UFUNCTION(BlueprintCallable)
	void Jump();
	
	void SetSettings(FMoveSettings NewSettings);
	
	
protected:
	
	//tries to move actor according to input from controller
	void SimpleMove(float DeltaTime);

	//adds final movement after actor has been snapped correctly to the ground
	// calculates movement such as:
	// gravitational
	//force
	void FinalMove(float DeltaTime);
	
	// checks if actor is on ground and sets bool bIsGrounded accordingly
	void GroundCheck();

	//searches for an object below pawn and snaps it to stand on it
	void SnapActorToGround();

	//calculates and sets gravity value
	void CalculateGravity(float DeltaTime);

	//calculate and remove force
	void CalculateForce(float DeltaTime);
	
	UPROPERTY(EditAnywhere, Category = "Movement settings")
	FMoveSettings Settings;
	
	FVector Force;
	FVector Velocity;
	FVector DirectionThisFrame;
	bool bJumpThisFrame;
	float GravitationalMovement;
	
	
};
