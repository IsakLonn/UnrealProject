// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core_Delegates.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECTCORE_API UCore_Delegates : public UObject
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE(FEmptyDelegate);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVectorDelegate, FVector, Vector);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVector2DDelegate, FVector2D, Vector2D);
};
