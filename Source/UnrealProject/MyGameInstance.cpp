// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"



UMyGameInstance::~UMyGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("The Pawn value is %s"), ( true ? TEXT("true") : TEXT("false") ));
}

ACameraManager* UMyGameInstance::CameraManager()
{

	if(CameraManagerInstance == nullptr)
	{
		CameraManagerInstance = GetWorld()->SpawnActor<ACameraManager>(ACameraManager::StaticClass(), FVector::Zero(), FRotator::ZeroRotator);
	}
	
	return CameraManagerInstance;
		IsValid(CameraManagerInstance) ?
		CameraManagerInstance :
		CameraManagerInstance = NewObject<ACameraManager>(this, FName("CameraManager"));
}


void UMyGameInstance::OnStart()
{
	Super::OnStart();
	UE_LOG(LogTemp, Warning, TEXT("The OnStart value is %s"), ( true ? TEXT("true") : TEXT("false") ));
}

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("The Init value is %s"), ( true ? TEXT("true") : TEXT("false") ));
}
