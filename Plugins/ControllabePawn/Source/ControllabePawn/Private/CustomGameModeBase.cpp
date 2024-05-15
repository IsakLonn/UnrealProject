// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameModeBase.h"

void ACustomGameModeBase::InitGameState()
{
	Super::InitGameState();

	DefaultPawnClass = CustomPawnClass;
	PlayerControllerClass = CustomPlayerController;
	
}

ACustomGameModeBase::ACustomGameModeBase()
{
	PlayerControllerClass = CustomPlayerController;
}
