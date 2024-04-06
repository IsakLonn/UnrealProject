// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "ControllablePawnMath.generated.h"

/**
 * 
 */
UCLASS()
class CONTROLLABEPAWN_API AControllablePawnMath : public AInfo
{
	GENERATED_BODY()

public:
	static float Angle(FVector V1, FVector V2);
	static bool WithinRange(float value, float min, float max);
};
