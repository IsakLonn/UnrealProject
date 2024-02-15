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
	UE_LOG(LogTemp, Warning, TEXT("The Pawn value is %s"), ( Pawn != nullptr ? TEXT("true") : TEXT("false") ));
	UE_LOG(LogTemp, Warning, TEXT("The DirectionalComponent value is %s"), ( DirectionalComponent != nullptr ? TEXT("true") : TEXT("false") ));
	UE_LOG(LogTemp, Warning, TEXT("The ControllerComponent value is %s"), ( ControllerComponent != nullptr ? TEXT("true") : TEXT("false") ));
	if (Pawn == nullptr || DirectionalComponent == nullptr || ControllerComponent == nullptr) return;
	 FVector NewLocation = Pawn->GetActorLocation();
	 FVector _Forward = ControllerComponent->GetForwardVector();
	 FVector _Right = ControllerComponent->GetRightVector();
	 FVector Input = ControllerComponent->GetControllerInput();
	
	 NewLocation += ((_Forward * Input.X) + (_Right * Input.Y)) * ActorSpeed;
	 Pawn->SetActorLocation(NewLocation);

	// find out which way is forward
	//const FRotator Rotation = ControllerComponent->GetControlRotation();
	//const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	//const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
	// get right vector 
	//const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//Pawn->AddMovementInput(ForwardDirection, ControllerInput.Y);
	//Pawn->AddMovementInput(RightDirection, ControllerInput.X);

	//UE_LOG(LogTemp, Warning, TEXT("The forward c: %s"), *ForwardDirection.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("The right c: %s"), *RightDirection.ToString());
	// UE_LOG(LogTemp, Warning, TEXT("The forward: %s"), *_Forward.ToString());
	// UE_LOG(LogTemp, Warning, TEXT("The right: %s"), *_Right.ToString());
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

void UMoveComponent::SetControllerComponent(UControllerComponent* _ControllerComponent)
{
	ControllerComponent = _ControllerComponent;
}

