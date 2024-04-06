// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControllablePawnBase.h"
#include "StateBase.h"
#include "PlayerBaseState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UPlayerBaseState : public UStateBase
{
	GENERATED_BODY()

public:
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

protected:
	UPROPERTY()
	AControllablePawnBase* PlayerRef;

	UPROPERTY(EditAnywhere)
	FMoveSettings MovementStateSettings;

	virtual void OnJumpInput();
	virtual void OnMovementInput(FVector Input);
};
