// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"
#include "IdlePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UIdlePlayerState : public UPlayerBaseState
{
public:
	virtual void OnJumpInput() override;
	virtual void OnMovementInput(FVector Input) override;

private:
	GENERATED_BODY()
};
