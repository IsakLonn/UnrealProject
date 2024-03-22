// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControllerComponent.h"
#include "UObject/Interface.h"
#include "ActorMovementInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActorMovementInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALPROJECT_API IActorMovementInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	virtual void MovementInput(UControllerComponent* Controller, FVector Input) = 0;
	virtual void JumpInput(UControllerComponent* Controller) = 0;
	virtual void CrouchInput(UControllerComponent Controller) = 0;
};
