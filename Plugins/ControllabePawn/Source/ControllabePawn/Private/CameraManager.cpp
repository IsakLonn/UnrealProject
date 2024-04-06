// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"

#include "Kismet/GameplayStatics.h"

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

void ACameraManager::AttachToComponent(USceneComponent* Target, float TargetArmLength, bool SnapToTarget) const
{
	Target = Target != nullptr ? Target : root;
	const FAttachmentTransformRules AttachmentTransformRules = SnapToTarget ? FAttachmentTransformRules::SnapToTargetNotIncludingScale : FAttachmentTransformRules::KeepWorldTransform;
	CameraBoom->AttachToComponent(Target, AttachmentTransformRules);
	SetTargetArmLength(TargetArmLength);
}

void ACameraManager::ReturnCamera() const
{
	AttachToComponent(nullptr, 0, false);
}

void ACameraManager::SetLocation(FVector Location, bool bRelativeLocation) const
{
	if(bRelativeLocation) CameraBoom->SetRelativeLocation(Location);
	else CameraBoom->SetWorldLocation(Location);
}

void ACameraManager::SetRotation(FRotator Rotation, bool bRelativeRotation) const
{
	if(bRelativeRotation) CameraBoom->SetRelativeRotation(Rotation);
	else CameraBoom->SetWorldRotation(Rotation);
}

void ACameraManager::SetTargetArmLength(float TargetArmLength) const
{
	CameraBoom->TargetArmLength = TargetArmLength;
}

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

		if(playerController != nullptr)playerController->SetViewTarget(this);
	}
}

USpringArmComponent* ACameraManager::GetCameraBoom() const
{
	return CameraBoom;
}

