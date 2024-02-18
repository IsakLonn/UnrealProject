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
	
}

void UMoveComponent::OrientVisualsWithMovement()
{
	if (Pawn == nullptr || Orientation == nullptr || Controller == nullptr) return;
	auto Input = Controller->GetMovementInput();
	auto Forward = Controller->GetForwardVector();
	auto Right = Controller->GetRightVector();
	if (Input.X == 0 && Input.Y == 0) return; // don't rotate player if no input exists
	FVector LookLocation = (Forward * Input.X) + (Right * Input.Y);
	FVector ActorLocation = Pawn->GetActorLocation();
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, ActorLocation + LookLocation);
	Rotation += VisualsDefaultRotation;
	Orientation->SetRelativeRotation(Rotation);
}

void UMoveComponent::SetActorSpeed(float speed) { ActorSpeed = speed; }

void UMoveComponent::TryMovePawn(float DeltaTime)
{
	//check for nullptr references
	if (Pawn == nullptr || Controller == nullptr) return;

	//get current position, input, and directional vectors
	FVector NewLocation = Pawn->GetActorLocation();
	FVector Forward = Controller->GetForwardVector();
	FVector Right = Controller->GetRightVector();
	FVector Up = Controller->GetUpVector();
	FVector Input = Controller->GetMovementInput();

	//update position
	NewLocation += ((Forward * Input.X) + (Right * Input.Y) + (Up * Input.Z)) * ActorSpeed;

	//set new position
	Pawn->SetActorLocation(NewLocation);

}

// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TryMovePawn(DeltaTime);
	if (OrientWithMovement) OrientVisualsWithMovement();
	// ...
}

void UMoveComponent::SetPawn(APawn* _Pawn)
{
	if (_Pawn == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Pawn sent in to SetPawn is null"));
		return;
	}
	Pawn = _Pawn;
}

void UMoveComponent::SetOrientation(USceneComponent* _Orientation)
{
	if (_Orientation == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Orientation sent in to SetOrientation is null"));
		return;
	}
	Orientation = _Orientation;
}

void UMoveComponent::SetController(UControllerComponent* _Controller)
{
	if (_Controller == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("ControllerComponent sent in to SetControllerComponent is null"));
		return;
	}
	Controller = _Controller;
}

