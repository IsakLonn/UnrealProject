// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControllablePawnBase.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CONTROLLABEPAWN_API ACustomGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void InitGameState() override;

	ACustomGameModeBase();

protected:
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<AControllablePawnBase> CustomPawnClass;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<APlayerController> CustomPlayerController;
};
