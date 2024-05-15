// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Core_Structs.generated.h"

USTRUCT()
struct FMoveSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float ActorSpeed = 10;
	UPROPERTY(EditAnywhere)
	float JumpStrength = 10;
	UPROPERTY(EditAnywhere, meta=(ClampMin="0", ClampMax="1"))
	float Friction = 1;

	UPROPERTY(EditAnywhere)
	bool bUseGravity = true;
	UPROPERTY(EditAnywhere, meta=(ClampMin="-90", ClampMax="0"))
	float Gravity = -9;

	UPROPERTY(EditAnywhere, meta=(ClampMin="0", ClampMax="90"))
	float MaxSlopeAngle = 45;
	
	UPROPERTY(EditAnywhere)
	bool OrientWithMovement = true;
	
	UPROPERTY(EditAnywhere)
	bool DebugGroundRayCast = true;
	UPROPERTY(EditAnywhere)
	bool ResetCurrentGravityOnJump = true;

	UPROPERTY(EditAnywhere, meta=(ClampMin="0", ClampMax="100"))
	float ForceDissipationPerFrame = 20;
	UPROPERTY(EditAnywhere, meta=(ClampMin="0", ClampMax="100"))
	float MaxAppliedForce = 50;

	bool bIsGrounded;
	
};

UCLASS()
class UNREALPROJECTCORE_API UCore_Structs : public UUserDefinedStruct
{
	GENERATED_BODY()
	
};
