// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorMovementStateMachine.h"

// Sets default values for this component's properties
UActorMovementStateMachine::UActorMovementStateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	GroundMovement = CreateDefaultSubobject<UActorGroundMovementComponent>(TEXT("GroundMovement"));
	// ...
}


// Called when the game starts
void UActorMovementStateMachine::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActorMovementStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActorMovementStateMachine::MovementInput(UControllerComponent* Controller, FVector Input)
{
	GroundMovement->MovementInput(Controller, Input);
}

void UActorMovementStateMachine::JumpInput(UControllerComponent* Controller)
{
	GroundMovement->JumpInput(Controller);
}

