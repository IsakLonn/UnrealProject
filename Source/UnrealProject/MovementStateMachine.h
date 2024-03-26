// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GroundMovementState.h"
#include "Components/SceneComponent.h"
#include "Enums.h"
#include "MovementStateMachine.generated.h"

UCLASS()
//Controller for delegating information about movement, such as pressing the jump key. Can be seen as a control center
class UNREALPROJECT_API UMovementStateMachine : public UPlayerComponentBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementStateMachine();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	

	void MovementInput(FVector Input);
	void JumpInput();

private:
	MovementState CurrentState;
	
	UPROPERTY(EditAnywhere)
	UGroundMovementState* GroundMovement;

	void SetState(MovementState NewState);
	
};
