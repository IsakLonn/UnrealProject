// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Movement/Core_ControlledPawn.h"
#include "Core_GameModeBase.generated.h"

UCLASS()
class UNREALPROJECTCORE_API ACore_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	virtual void InitGameState() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACore_ControlledPawn> DefaultPawn;
};
