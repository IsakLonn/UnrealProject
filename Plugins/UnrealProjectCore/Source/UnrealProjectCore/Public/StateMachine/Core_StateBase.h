// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core_StateBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UNREALPROJECTCORE_API UCore_StateBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bCanRepeat = false;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName StateDisplayname;

	virtual void OnEnterState(AActor* StateOwner);
	virtual void TickState();
	virtual void OnExitState();
};
