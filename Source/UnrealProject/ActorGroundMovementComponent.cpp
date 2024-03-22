// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorGroundMovementComponent.h"

void UActorGroundMovementComponent::MovementInput(UControllerComponent* Controller, FVector Input)
{
	Controller->SetMovementInputX(Input.X);
	Controller->SetMovementInputY(Input.Y);
}

void UActorGroundMovementComponent::JumpInput(UControllerComponent* Controller)
{
	Controller->SetIsJumping(true);
}

void UActorGroundMovementComponent::CrouchInput(UControllerComponent Controller)
{
}

// Sets default values for this component's properties
UActorGroundMovementComponent::UActorGroundMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorGroundMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UActorGroundMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


