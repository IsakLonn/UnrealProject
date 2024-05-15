// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstanceBase.h"

ACameraManager* UCustomGameInstanceBase::GetCameraManager()
{
	if(CameraManagerInstance == nullptr)
	{
		CameraManagerInstance = GetWorld()->SpawnActor<ACameraManager>(CameraManager);
		CameraManagerInstance->Initiate();
	}
	return CameraManagerInstance;
}
