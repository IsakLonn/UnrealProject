// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementStateMachine.h"
#include "MoveComponent.h"

// Sets default values for this component's properties
UMovementStateMachine::UMovementStateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	GroundMovement = CreateDefaultSubobject<UGroundMovementState>(TEXT("GroundMovement"));
	// ...
}


// Called when the game starts
void UMovementStateMachine::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->GetComponentByClass<UMoveComponent>()->GetSettings();
	GroundMovement->ChangeMovementState.BindUObject(this, &UMovementStateMachine::SetState);

	SetState(Ground);
	// ...
	
}

void UMovementStateMachine::MovementInput(FVector Input)
{
	switch (CurrentState) {
	case Jumping:
		break;
	case Ground:
		GroundMovement->MovementInput(Input);
		break;
	case Flying:
		break;
	case Swimming:
		break;
	}
	
}

void UMovementStateMachine::JumpInput()
{
	switch (CurrentState) {
	case Jumping:
		break;
	case Ground:
		GroundMovement->JumpInput();
		break;
	case Flying:
		break;
	case Swimming:
		break;
	}
	
}

void UMovementStateMachine::SetState(MovementState NewState)
{
	CurrentState = NewState;
	switch (CurrentState) {
	case Jumping:
		break;
	case Ground:
		GroundMovement->EnterState();
		break;
	case Flying:
		break;
	case Swimming:
		break;
	}
}

