// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/Core_PlayerController.h"
#include "Movement/Core_ControlledPawn.h"
#include "StateMachine/Core_StateBase.h"
#include "Core_CameraStateBase.generated.h"

UCLASS()
class UNREALPROJECTCORE_API UCore_CameraStateBase : public UCore_StateBase, public ICore_IInputListener
{
	GENERATED_BODY()
public:
    virtual void OnEnterState(AActor* StateOwner) override;
	
	virtual void OnMovement_Implementation(FVector Movement) override;
	virtual void OnRotation_Implementation(FVector2D Rotation) override;

protected:

	UPROPERTY()
	ACore_ControlledPawn* PossessedPawn;

	UPROPERTY()
	UCore_PawnController* Controller;

	UPROPERTY()
	ACore_PlayerCameraManager* PlayerCameraManager;
	
};
