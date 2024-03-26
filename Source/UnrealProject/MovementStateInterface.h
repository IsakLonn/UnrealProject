// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "UObject/Interface.h"
#include "MovementStateInterface.generated.h"


DECLARE_DELEGATE_OneParam(MovementStateDelegate, MovementState);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMovementStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALPROJECT_API IMovementStateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	virtual void MovementInput(FVector Input) = 0;
	virtual void JumpInput() = 0;
	virtual void CrouchInput() = 0;
	virtual void EnterState() = 0;

	MovementStateDelegate ChangeMovementState;
};
