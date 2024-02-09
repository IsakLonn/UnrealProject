// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	SetMovementSpeed(WalkSpeed);
	
}

void UMoveComponent::OrientVisualsWithMovement()
{
	if (Pawn == nullptr || Orientation == nullptr || PlayerForwardRight == nullptr) return;
	if (!bCanRotate) return;
	if (MovementInput.X == 0 && MovementInput.Y == 0) return; // don't rotate player if no input exists
	FVector LookLocation = (PlayerForwardRight->GetForwardVector() * MovementInput.X) + (PlayerForwardRight->GetRightVector() * MovementInput.Y);
	FVector ActorLocation = Pawn->GetActorLocation();
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, ActorLocation + LookLocation);
	Rotation += VisualsDefaultRotation;
	Orientation->SetRelativeRotation(Rotation);
}

void UMoveComponent::SetMovementInputLR(float Value) { MovementInput.Y = Value; }

void UMoveComponent::SetMovementInputFB(float Value) { MovementInput.X = Value; }

void UMoveComponent::ToggleRotation(bool toggle) { bCanRotate = toggle; }

void UMoveComponent::ToggleMovement(bool toggle) { bCanMove = toggle; }

void UMoveComponent::SetMovementSpeed(float speed) { currentSpeed = speed; }

void UMoveComponent::TryMovePlayer(float DeltaTime)
{
	if (Pawn == nullptr || PlayerForwardRight == nullptr) return;
	if (!bCanMove) return;

	FVector NewLocation = Pawn->GetActorLocation();
	FVector _Forward = PlayerForwardRight->GetForwardVector();
	FVector _Right = PlayerForwardRight->GetRightVector();

	NewLocation += ((_Forward * MovementInput.X) + (_Right * MovementInput.Y)) * currentSpeed;
	Pawn->SetActorLocation(NewLocation);
}

// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TryMovePlayer(DeltaTime);
	// ...
}

void UMoveComponent::Setup(APawn* _Pawn, USceneComponent* _Orientation, USceneComponent* _PlayerForwardRight)
{
	Pawn = _Pawn;
	Orientation = _Orientation;
	PlayerForwardRight = _PlayerForwardRight;
	VisualsDefaultRotation = Orientation->GetRelativeRotation();
}

