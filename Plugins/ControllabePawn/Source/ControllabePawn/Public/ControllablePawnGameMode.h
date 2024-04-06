// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ControllablePawnGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CONTROLLABEPAWN_API AControllablePawnGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void InitGameState() override;

protected:
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<AControllablePawnBase> CustomPawnClass;
};
