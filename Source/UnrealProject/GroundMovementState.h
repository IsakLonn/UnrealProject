// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementStateInterface.h"
#include "PlayerComponentBase.h"
#include "Structs.h"
#include "Components/SceneComponent.h"
#include "GroundMovementState.generated.h"

UCLASS()
class UNREALPROJECT_API UGroundMovementState : public UPlayerComponentBase, public IMovementStateInterface
{
public:
	virtual void EnterState() override;

	virtual void MovementInput(FVector Input) override;
	virtual void JumpInput() override;
	virtual void CrouchInput() override;

	UPROPERTY(EditAnywhere)
	FMoveSettings GroundMovementSettings;

private:
	GENERATED_BODY()

};
