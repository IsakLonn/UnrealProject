// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllablePawnGameMode.h"

void AControllablePawnGameMode::InitGameState()
{
	Super::InitGameState();

	DefaultPawnClass = CustomPawnClass;
	
	
}