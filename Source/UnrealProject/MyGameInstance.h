// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraManager.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	// UFUNCTION(BlueprintPure, Category = "Persistence", meta = ( DisplayName = "Get Camera Manager", Keywords = "CameraManager"))
	ACameraManager* CameraManager();

protected:

	// UPROPERTY(Transient)
	ACameraManager* CameraManagerInstance;

};
