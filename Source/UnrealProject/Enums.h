// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "Enums.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum MovementState
{
	Jumping     UMETA(DisplayName = "Jumping/Falling"),
	Ground,
	Flying,
	Swimming
  };
UCLASS()
class UNREALPROJECT_API UEnums : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};
