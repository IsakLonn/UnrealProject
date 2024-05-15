// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/Core_ControlledPawn.h"

// Sets default values
ACore_ControlledPawn::ACore_ControlledPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create root component
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = Collider;
	
	//create movement component
	PawnMovement = CreateDefaultSubobject<UCore_PawnMovement>(TEXT("PawnMovement"));

	//create mesh parent, used for "rotating pawn"
	OrientationParent = CreateDefaultSubobject<USceneComponent>(TEXT("OrientationParent"));
	OrientationParent->SetupAttachment(RootComponent);

	//create controller for pawn
	StateManager = CreateDefaultSubobject<UCore_StateManager>(TEXT("StateManager"));

	//create skeleton mesh
	PawnMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(OrientationParent);

}

void ACore_ControlledPawn::BeginPlay()
{
	Super::BeginPlay();
	StateManager->InitStateManager();
}

USceneComponent* ACore_ControlledPawn::GetOrientationParent() const
{
	return OrientationParent;
}

UCore_PawnMovement* ACore_ControlledPawn::GetMovementComponent() const
{
	return PawnMovement;
}

// void ACore_ControlledPawn::RotateTowardsMovement(float DeltaTime, float RotationSpeed) const
// {
//  	
// 	FVector Direction = PawnMovement->GetVelocity();
// 	Direction.Z = 0;
// 	
// 	FVector ActorLocation = OrientationParent->GetComponentLocation();
// 	FRotator Target = UKismetMathLibrary::FindLookAtRotation(ActorLocation, ActorLocation + Direction);
// 	FRotator CalculatedRotation = FMath::RInterpTo(OrientationParent->GetComponentRotation(), Target, DeltaTime, RotationSpeed);
//
// 	
// 	if (Direction.X == 0 && Direction.Y == 0) return;
// 	
// 	OrientationParent->SetRelativeRotation(CalculatedRotation);
// }

