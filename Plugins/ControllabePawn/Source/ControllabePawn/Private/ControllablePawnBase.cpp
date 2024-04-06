// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllablePawnBase.h"

#include "ControllablePawnGameInstance.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AControllablePawnBase::AControllablePawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create root component
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = Collider;
	
	//create movement component
	PawnMovement = CreateDefaultSubobject<UControllablePawnMovement>(TEXT("PawnMovement"));

	//create object rotated
	OrientationParent = CreateDefaultSubobject<USceneComponent>(TEXT("OrientationParent"));
	OrientationParent->SetupAttachment(RootComponent);

	//create controller for pawn
	PawnController = CreateDefaultSubobject<UPawnController>(TEXT("PawnController"));

	//create skeleton mesh
	PawnMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(OrientationParent);

	//create skeleton mesh
	FPSCamTarget = CreateDefaultSubobject<USceneComponent>(TEXT("FPSCamTarget"));
	FPSCamTarget->SetupAttachment(OrientationParent);

	//create skeleton mesh
	TPSCamTarget = CreateDefaultSubobject<USceneComponent>(TEXT("TPSCamTarget"));
	TPSCamTarget->SetupAttachment(Collider);

}

// Called when the game starts or when spawned
void AControllablePawnBase::BeginPlay()
{
	Super::BeginPlay();
	
	
	
	SetPerspective(TPS);
	
}

void AControllablePawnBase::OnJumpInput() { PawnController->SetIsJumping(); }

void AControllablePawnBase::OnToggleCrouch(bool toggle)
{
	
}

void AControllablePawnBase::OnToggleSprint(bool toggle)
{
	
}

void AControllablePawnBase::OnRotationInput(FVector2D Input)
{
	PawnController->SetRotationInput(Input);

	auto UDRot = CamRotUDTarget->GetRelativeRotation();
	auto LRRot = CamRotLRTarget->GetRelativeRotation();

	//update rotations
	LRRot.Yaw += Input.Y;
	UDRot.Pitch += Input.X;
	UDRot.Pitch = FMath::Clamp(UDRot.Pitch, -45, 45);

	//set new rotations
	CamRotLRTarget->SetRelativeRotation(LRRot);
	CamRotUDTarget->SetRelativeRotation(UDRot);
}

void AControllablePawnBase::OnMovementInput(FVector Input) { PawnController->SetMovementInput(Input); }

void AControllablePawnBase::SetPerspective(Perspectives NewPerspective)
{
	const auto CamManager = Cast<UControllablePawnGameInstance>(GetWorld()->GetGameInstance())->GetCameraManager();
	switch (NewPerspective)
	{
	case FPS:
		CamManager->AttachToComponent(FPSCamTarget, 0);
		CamRotLRTarget = OrientationParent;
		CamRotUDTarget = FPSCamTarget;
		break;

	case TPS:
		CamManager->AttachToComponent(TPSCamTarget, 100);
		CamRotLRTarget = TPSCamTarget;
		CamRotUDTarget = CamManager->GetCameraBoom();
		break;
	}

	PawnController->SetForwardComponentReference(CamRotUDTarget);
	PawnController->SetUpComponentReference(RootComponent);
	PawnController->SetRightComponentReference(CamRotLRTarget);
}

UPawnController* AControllablePawnBase::GetPawnController() { return PawnController; }

UCapsuleComponent* AControllablePawnBase::GetCollider() { return Collider; }

// void UControllablePawnMovement::RotateTowardsMovement(float DeltaTime, float RotationSpeed) const
// {
// 	
// 	//get data from controller
// 	auto Input = GetControllablePawn()->GetPawnController()->ConsumeMovementInput();
// 	auto Forward = GetControllablePawn()->GetPawnController()->GetForwardVector();
// 	auto Right = GetControllablePawn()->GetPawnController()->GetRightVector();
//
// 	// don't rotate player if no input exists
// 	if (Input.X == 0 && Input.Y == 0) return; 
//
// 	//calculate rotation
// 	
// 	FVector Direction = Velocity;
// 	FVector ActorLocation = UpdatedComponent->GetComponentLocation();
// 	FRotator Target = UKismetMathLibrary::FindLookAtRotation(ActorLocation, ActorLocation + Direction);
// 	//FRotator CalculatedRotation = FMath::RInterpTo(Orientation->GetComponentRotation(), Target, DeltaTime, RotationSpeed);
// 	
// 	//Orientation->SetRelativeRotation(CalculatedRotation);
// }