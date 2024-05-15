// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACameraManager::ACameraManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = root;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(root);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraBoom);

}

void ACameraManager::AttachToComponent(USceneComponent* Target) const
{
	if(Target == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Camera attach target was null"));
		return;
	}
	CameraBoom->AttachToComponent(Target, FAttachmentTransformRules::KeepWorldTransform);
}

void ACameraManager::ReturnCamera() const{ AttachToComponent(root); }

void ACameraManager::SetTargetArmLength(float TargetArmLength) const
{
	CameraBoom->TargetArmLength = TargetArmLength;
}

void ACameraManager::SetTargetOffset(FVector offset) { CameraBoom->SetWorldLocation(offset); }

void ACameraManager::SetFOV(float FOV) const
{
	Camera->SetFieldOfView(FOV);
}

void ACameraManager::Initiate()
{
	const auto world = GetWorld();
	if(world == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error getting world when setting up CameraManager"));
	}
	else
	{
		const auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		//if(playerController != nullptr)playerController->SetViewTarget(this);
	}
}

void ACameraManager::LookTowards(FVector TargetLocation)
{
	
	FVector ActorLocation = RootComponent->GetComponentLocation();
	
	FRotator Target = UKismetMathLibrary::FindLookAtRotation(ActorLocation, ActorLocation + TargetLocation);

	CameraBoom->SetWorldRotation(Target);
	
}

USpringArmComponent* ACameraManager::GetCameraBoom() const
{
	return CameraBoom;
}

