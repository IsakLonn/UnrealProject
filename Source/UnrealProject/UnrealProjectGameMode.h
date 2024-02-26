// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerPawn.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealProjectGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API AUnrealProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void InitGameState() override;

protected:


	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<APlayerPawn> CustomPawnClass = APlayerPawn::StaticClass();
	
};
