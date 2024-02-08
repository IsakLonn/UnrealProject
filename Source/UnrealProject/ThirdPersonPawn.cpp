// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonPawn.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AThirdPersonPawn::AThirdPersonPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = Collider;

	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(RootComponent);

	CameraForward = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraForward"));
	CameraForward->SetupAttachment(RootComponent);

	MoveComponent = CreateDefaultSubobject<UMoveComponent>(TEXT("MoveComponent"));
	MoveComponent->SetupAttachment(RootComponent);	

	CamComponent = CreateDefaultSubobject<UCamComponent>(TEXT("CamComponent"));
	CamComponent->SetupAttachment(RootComponent);

	CameraParent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraParent"));
	CameraParent->SetupAttachment(CameraForward);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	Camera->SetupAttachment(CameraParent);

	MoveComponent->Setup(this, CameraForward, CameraParent, PlayerMesh);

}


void AThirdPersonPawn::SetRotationInputLR(float Value)
{
	RotationInput.Y = Value;
}

void AThirdPersonPawn::SetRotationInputUD(float Value)
{
	RotationInput.X = Value;
}

// Called when the game starts or when spawned
void AThirdPersonPawn::BeginPlay()
{
	Super::BeginPlay();
	CamComponent->Setup(CameraForward, CameraParent);
}

void AThirdPersonPawn::TryRotateCamera(float DeltaTime)
{
	auto CamParentRot = CameraParent->GetRelativeRotation();
	auto CamForwardRot = CameraForward->GetRelativeRotation();

	CamForwardRot.Yaw += RotationInput.Y * CamRotSpeed * DeltaTime;
	CamParentRot.Pitch += RotationInput.X * CamRotSpeed * DeltaTime;
	CamParentRot.Pitch = FMath::Clamp(CamParentRot.Pitch, CameraUDMinPitch, CameraUDMaxPitch);

	CameraParent->SetRelativeRotation(CamParentRot);
	CameraForward->SetRelativeRotation(CamForwardRot);
}

// Called every frame
void AThirdPersonPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TryRotateCamera(DeltaTime);
}

// Called to bind functionality to input
void AThirdPersonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

