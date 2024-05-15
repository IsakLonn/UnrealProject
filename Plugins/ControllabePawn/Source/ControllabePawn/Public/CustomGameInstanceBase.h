// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraManager.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class CONTROLLABEPAWN_API UCustomGameInstanceBase : public UGameInstance
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
