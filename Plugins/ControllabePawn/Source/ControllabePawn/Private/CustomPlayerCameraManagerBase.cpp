// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerCameraManagerBase.h"

#include "Kismet/KismetMathLibrary.h"

ACustomPlayerCameraManagerBase::ACustomPlayerCameraManagerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	CameraRoot = CreateDefaultSubobject<USceneComponent>("CameraRoot");
	CameraRoot->SetupAttachment(RootComponent);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(CameraRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraBoom);
}

void ACustomPlayerCameraManagerBase::BeginPlay()
{
	
	Super::BeginPlay();
	SetViewTarget(this);
	
	//CameraBoom->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}


void ACustomPlayerCameraManagerBase::AttachToComponent(USceneComponent* Target) const { CameraRoot->AttachToComponent(Target, FAttachmentTransformRules::KeepWorldTransform); }

void ACustomPlayerCameraManagerBase::DeAttachCamera() const{ AttachToComponent(nullptr); }

void ACustomPlayerCameraManagerBase::SetTargetArmLength(float TargetArmLength) const { CameraBoom->TargetArmLength = TargetArmLength; }

void ACustomPlayerCameraManagerBase::TickActor(float DeltaTime, ELevelTick TickType,
                                               FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);
	
}

void ACustomPlayerCameraManagerBase::SetLocation(FVector Location, bool bIsWorldLocation) {  bIsWorldLocation ? CameraRoot->SetWorldLocation(Location) : CameraRoot->SetRelativeLocation(Location); }

void ACustomPlayerCameraManagerBase::RotateZAxis(float Value)
{

	auto RotValue = CameraBoom->GetRelativeRotation();

	//update rotations
	RotValue.Yaw += Value;

	//set new rotations
	CameraBoom->SetRelativeRotation(RotValue);
}

void ACustomPlayerCameraManagerBase::RotateYAxis(float Value)
{
	auto RotValue = CameraBoom->GetRelativeRotation();

	//update rotations
	RotValue.Pitch += Value;
	RotValue.Pitch = FMath::Clamp(RotValue.Pitch, MinZRot, MaxZRot);
	
	//set new rotations
	CameraBoom->SetRelativeRotation(RotValue);
}

//sets the min and max for rotating Z(yaw).
//parameters sent in gets clamped in case any parameter is set too high/low
void ACustomPlayerCameraManagerBase::SetZRotClamp(float Min, float Max)
{
	MinZRot = FMath::Clamp(Min, -89, 0);
	MaxZRot = FMath::Clamp(Max, 1, 89);
}

void ACustomPlayerCameraManagerBase::LookTowards(const FVector Vector)
{
	FVector CamBoomLocation = CameraRoot->GetComponentLocation();
	
	FRotator Target = UKismetMathLibrary::FindLookAtRotation(CamBoomLocation, CamBoomLocation + Vector);

	CameraRoot->SetWorldRotation(Target);
}


