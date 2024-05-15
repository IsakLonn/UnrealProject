// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/PawnMovementState/Core_PawnMovementStateBase.h"
#include "Core_GroundMovementState.generated.h"

UCLASS()
class UNREALPROJECTCORE_API UCore_GroundMovementState : public UCore_PawnMovementStateBase
{
	GENERATED_BODY()

	virtual void OnMovement_Implementation(FVector Movement) override;
	virtual void OnJump_Implementation() override;
	
};
