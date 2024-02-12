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
	if (Pawn == nullptr || Orientation == nullptr || DirectionalComponent == nullptr) return;
	if (ControllerInput.X == 0 && ControllerInput.Y == 0) return; // don't rotate player if no input exists
	FVector LookLocation = (DirectionalComponent->GetForwardVector() * ControllerInput.X) + (DirectionalComponent->GetRightVector() * ControllerInput.Y);
	FVector ActorLocation = Pawn->GetActorLocation();
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, ActorLocation + LookLocation);
	Rotation += VisualsDefaultRotation;
	Orientation->SetRelativeRotation(Rotation);
}

void UMoveComponent::SetControllerInputLR(float Value) { ControllerInput.Y = Value; }

void UMoveComponent::SetControllerInputFB(float Value) { ControllerInput.X = Value; }

void UMoveComponent::SetControllerInputUD(float Value) { ControllerInput.Z = Value; }

void UMoveComponent::SetActorSpeed(float speed) { ActorSpeed = speed; }

void UMoveComponent::TryMovePawn(float DeltaTime)
{
	if (Pawn == nullptr || DirectionalComponent == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *ControllerInput.ToString());
	FVector NewLocation = Pawn->GetActorLocation();
	FVector _Forward = DirectionalComponent->GetForwardVector();
	FVector _Right = DirectionalComponent->GetRightVector();
	FVector _Up = DirectionalComponent->GetUpVector();

	NewLocation += ((_Forward * ControllerInput.X) + (_Right * ControllerInput.Y) + (_Up * ControllerInput.Z)) * ActorSpeed;
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

void UMoveComponent::Setup(APawn* _Pawn, USceneComponent* _Orientation, USceneComponent* _DirectionalComponent)
{
	SetPawn(_Pawn);
	SetOrientation(_Orientation);
	SetDirectionalComponent(_DirectionalComponent);
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

void UMoveComponent::SetDirectionalComponent(USceneComponent* _DirectionalComponent)
{
	if (_DirectionalComponent == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("DirectionalComponent sent in to SetDirectionalComponent is null"));
		return;
	}
	DirectionalComponent = _DirectionalComponent;
	VisualsDefaultRotation = Orientation->GetRelativeRotation();
}

