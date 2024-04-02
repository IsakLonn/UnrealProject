// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"
#include "JumpPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UJumpPlayerState : public UPlayerBaseState
{
public:
	virtual void OnJumpInput() override;
	virtual void OnMovementInput(FVector Input) override;
	virtual void TickState() override;

private:
	GENERATED_BODY()
};
