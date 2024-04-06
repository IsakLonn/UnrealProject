// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllablePawnGameInstance.h"

ACameraManager* UControllablePawnGameInstance::GetCameraManager()
{
	if(CameraManagerInstance == nullptr)
	{
		CameraManagerInstance = GetWorld()->SpawnActor<ACameraManager>(CameraManager);
		CameraManagerInstance->Initiate();
	}
	return CameraManagerInstance;
}
