// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Structs.generated.h"

/**
 * 
 */
USTRUCT()
struct FMoveSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float ActorSpeed;
	UPROPERTY(EditAnywhere)
	float JumpStrength;
	UPROPERTY(EditAnywhere, meta=(ClampMin="0", ClampMax="1"))
	float Friction;

	UPROPERTY(EditAnywhere)
	bool bUseGravity;
	UPROPERTY(EditAnywhere, meta=(ClampMin="-90", ClampMax="0"))
	float Gravity;

	UPROPERTY(EditAnywhere, meta=(ClampMin="0", ClampMax="90"))
	float MaxSlopeAngle;
	
	UPROPERTY(EditAnywhere)
	bool OrientWithMovement = true;
	
	UPROPERTY(EditAnywhere)
	bool DebugGroundRayCast = true;

	UPROPERTY(EditAnywhere, meta=(ClampMin="0", ClampMax="100"))
	float ForceDissipationPerFrame;
	UPROPERTY(EditAnywhere, meta=(ClampMin="0", ClampMax="100"))
	float MaxAppliedForce;

	bool bIsGrounded;
};

UCLASS()
class UNREALPROJECT_API UStructs : public UUserDefinedStruct
{
	GENERATED_BODY()
	
};
