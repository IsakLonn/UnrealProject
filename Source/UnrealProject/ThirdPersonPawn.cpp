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

	CameraParent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraParent"));
	CameraParent->SetupAttachment(CameraForward);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	Camera->SetupAttachment(CameraParent);

}


void AThirdPersonPawn::SetRotationInputLR(float Value)
{
	RotationInput.Y = Value;
}

void AThirdPersonPawn::SetRotationInputUD(float Value)
{
	RotationInput.X = Value;
}

void AThirdPersonPawn::SetMovementInputLR(float Value)
{	
	MovementInput.Y = Value;
}

void AThirdPersonPawn::SetMovementInputFB(float Value)
{
	MovementInput.X = Value;
}

void AThirdPersonPawn::OrientPlayerWithMovement()
{
	if (!RotationEnabled) return;
	if (MovementInput.X == 0 && MovementInput.Y == 0) return; // don't rotate player if no input exists
	FVector LookLocation = (CameraForward->GetForwardVector() * MovementInput.X) + (CameraForward->GetRightVector() * MovementInput.Y);
	FVector ActorLocation = GetActorLocation();
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, ActorLocation + LookLocation);
	Rotation += PlayerMeshDefaultRotation;
	PlayerMesh->SetRelativeRotation(Rotation);
}

void AThirdPersonPawn::ToggleMovement(bool toggle)
{
	MovementEnabled = toggle;
}

void AThirdPersonPawn::ToggleRotation(bool toggle)
{
	RotationEnabled = toggle;
}

void AThirdPersonPawn::SetMovementSpeed(float speed)
{
	CurrentMovementSpeed = speed;
}

// Called when the game starts or when spawned
void AThirdPersonPawn::BeginPlay()
{
	Super::BeginPlay();

	// setup default values
	PlayerMeshDefaultRotation = PlayerMesh->GetRelativeRotation();
	SetMovementSpeed(WalkSpeed);
}

void AThirdPersonPawn::TryMovePlayer(float DeltaTime)
{
	if (!MovementEnabled) return;
	FVector NewLocation = GetActorLocation();
	NewLocation += (CameraForward->GetForwardVector() * MovementInput.X + (CameraForward->GetRightVector() * MovementInput.Y)) * CurrentMovementSpeed;
	SetActorLocation(NewLocation);
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
	TryMovePlayer(DeltaTime);
	TryRotateCamera(DeltaTime);
}

// Called to bind functionality to input
void AThirdPersonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

