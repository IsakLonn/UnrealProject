// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Core_IInputListener.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCore_IInputListener : public UInterface
{
	GENERATED_BODY()
};

// an interface for subscribing to input from the pawncontroller
class UNREALPROJECTCORE_API ICore_IInputListener
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void OnMovement(FVector Movement);
	UFUNCTION(BlueprintNativeEvent)
	void OnRotation(FVector2D Rotation);
	UFUNCTION(BlueprintNativeEvent)
	void OnJump();
};
