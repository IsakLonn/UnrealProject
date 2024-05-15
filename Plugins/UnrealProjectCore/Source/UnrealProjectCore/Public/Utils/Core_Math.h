// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Core_Math.generated.h"

UCLASS()
class UNREALPROJECTCORE_API UCore_Math : public UObject
{
	GENERATED_BODY()

public:
	static float Angle(FVector V1, FVector V2);
	static bool WithinRange(float value, float min, float max);
	
};
