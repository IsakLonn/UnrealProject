// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraManager.h"
#include "Engine/GameInstance.h"
#include "ControllablePawnGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CONTROLLABEPAWN_API UControllablePawnGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	ACameraManager* GetCameraManager();

protected:

	UPROPERTY()
	ACameraManager* CameraManagerInstance;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<ACameraManager> CameraManager;
	
};
