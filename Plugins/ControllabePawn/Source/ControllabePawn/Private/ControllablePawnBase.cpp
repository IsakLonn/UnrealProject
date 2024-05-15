// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllablePawnBase.h"

#include "CustomGameInstanceBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	//create mesh parent, used for "rotating pawn"
	OrientationParent = CreateDefaultSubobject<USceneComponent>(TEXT("OrientationParent"));
	OrientationParent->SetupAttachment(RootComponent);

	//create controller for pawn
	PawnController = CreateDefaultSubobject<UPawnController>(TEXT("PawnController"));

	//create skeleton mesh
	PawnMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(OrientationParent);

	//create first person cam target
	FPSCamTarget = CreateDefaultSubobject<USceneComponent>(TEXT("FPSCamTarget"));
	FPSCamTarget->SetupAttachment(OrientationParent);

	//create third person cam target
	TPSCamTarget = CreateDefaultSubobject<USceneComponent>(TEXT("TPSCamTarget"));
	TPSCamTarget->SetupAttachment(Collider);

}

void AControllablePawnBase::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	CalculateControllerDirectionVectors();
	if(CurrentPerspective != FPS)RotateTowardsMovement(DeltaTime, 1);
}

// Called when the game starts or when spawned
void AControllablePawnBase::BeginPlay()
{
	Super::BeginPlay();

	//SetPerspective(SCW);
	
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
	if(!bAllowRotation) return;
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

void AControllablePawnBase::OnMovementInput(FVector Input)
{
	PawnController->SetMovementInput(Input);
}

void AControllablePawnBase::SetPerspective(Perspectives NewPerspective)
{
	//allow rotations by default when changing perspective
	bAllowRotation = true;
	
	CurrentPerspective = NewPerspective;
	
	const auto CamManager = Cast<UCustomGameInstanceBase>(GetWorld()->GetGameInstance())->GetCameraManager();
	
	switch (CurrentPerspective)
	{
	case FPS:
		CamManager->AttachToComponent(FPSCamTarget);
		CamRotLRTarget = OrientationParent;
		CamRotUDTarget = FPSCamTarget;
		break;

	case TPS:
		CamManager->AttachToComponent(TPSCamTarget);
		CamRotLRTarget = TPSCamTarget;
		CamRotUDTarget = CamManager->GetCameraBoom();
		break;

	case TDW:
		CamManager->AttachToComponent(RootComponent);
		CamManager->SetTargetOffset(RootComponent->GetComponentLocation() + (RootComponent->GetUpVector() * 1000));
		CamManager->LookTowards(-RootComponent->GetUpVector());
		bAllowRotation = false;
		break;

	case SCW:
		bAllowRotation = false;
		break;
	}
}

UPawnController* AControllablePawnBase::GetPawnController()
{
	return PawnController;
}

USceneComponent* AControllablePawnBase::GetTPCamTarget()
{
	return TPSCamTarget;
}

USceneComponent* AControllablePawnBase::GetFPCamTarget()
{
	return FPSCamTarget;
}

void AControllablePawnBase::RotateTowardsMovement(float DeltaTime, float RotationSpeed) const
{
 	
	FVector Direction = PawnMovement->GetVelocity();
	Direction.Z = 0;
	
	FVector ActorLocation = OrientationParent->GetComponentLocation();
	FRotator Target = UKismetMathLibrary::FindLookAtRotation(ActorLocation, ActorLocation + Direction);
	FRotator CalculatedRotation = FMath::RInterpTo(OrientationParent->GetComponentRotation(), Target, DeltaTime, RotationSpeed);

	
	if (Direction.X == 0 && Direction.Y == 0) return;
	
	OrientationParent->SetRelativeRotation(CalculatedRotation);
}

void AControllablePawnBase::CalculateControllerDirectionVectors()
{
	PawnController->SetForwardVector(FVector::ForwardVector);
	PawnController->SetUpVector(RootComponent->GetUpVector());
	PawnController->SetRightVector(FVector::RightVector);
	// switch (CurrentPerspective)
	// {
	// case FPS:
	// case TPS:
	// 	PawnController->SetForwardVector(CamRotLRTarget->GetForwardVector());
	// 	PawnController->SetUpVector(RootComponent->GetUpVector());
	// 	PawnController->SetRightVector(CamRotUDTarget->GetRightVector());
	// 	break;
	//
	// case TDW:
	// 	PawnController->SetForwardVector(FVector::ForwardVector);
	// 	PawnController->SetUpVector(FVector::UpVector);
	// 	PawnController->SetRightVector(FVector::RightVector);
	// 	break;
	// 	
	// case SCW:
	// 	const auto CamManager = Cast<UCustomGameInstanceBase>(GetWorld()->GetGameInstance())->GetCameraManager();
	// 	auto camBoom = CamManager->GetCameraBoom();
	// 	PawnController->SetForwardVector(UKismetMathLibrary::ProjectVectorOnToPlane(camBoom->GetForwardVector(), RootComponent->GetUpVector()));
	// 	PawnController->SetUpVector(RootComponent->GetUpVector());
	// 	PawnController->SetRightVector(UKismetMathLibrary::ProjectVectorOnToPlane(camBoom->GetRightVector(), RootComponent->GetUpVector()));
	// 	break;
	// }
	
	
}
