// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"


ACameraManager* UMyGameInstance::CameraManager()
{

	if(CameraManagerInstance == nullptr) CameraManagerInstance = GetWorld()->SpawnActor<ACameraManager>(ACameraManager::StaticClass(), FVector::Zero(), FRotator::ZeroRotator);

	return CameraManagerInstance;
}
