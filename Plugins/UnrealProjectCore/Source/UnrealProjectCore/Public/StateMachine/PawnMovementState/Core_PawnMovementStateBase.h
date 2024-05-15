// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movement/Core_ControlledPawn.h"
#include "StateMachine/Core_StateBase.h"
#include "Core_PawnMovementStateBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECTCORE_API UCore_PawnMovementStateBase : public UCore_StateBase, public ICore_IInputListener
{
	GENERATED_BODY()

public:
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

protected:
	UPROPERTY()
	ACore_ControlledPawn* PlayerRef;
	UPROPERTY()
	UCore_PawnController* Controller;

	UPROPERTY(EditAnywhere)
	FMoveSettings MovementStateSettings;

	virtual void OnMovement_Implementation(FVector Movement) override;
	virtual void OnRotation_Implementation(FVector2D Rotation) override;
	virtual void OnJump_Implementation() override;
	
};
