// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"

#include "ControllerComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GroundCheck();
	TryMovePawn(DeltaTime);
	if(OrientWithMovement) OrientVisualsWithMovement();
}

void UMoveComponent::OrientVisualsWithMovement()
{
	//nullchecks
	if (Orientation == nullptr || Controller == nullptr) return;

	//get data from controller
	auto Input = Controller->GetMovementInput();
	auto Forward = Controller->GetForwardVector();
	auto Right = Controller->GetRightVector();

	// don't rotate player if no input exists
	if (Input.X == 0 && Input.Y == 0) return; 

	//calculate rotation
	FVector LookLocation = (Forward * Input.X) + (Right * Input.Y);
	FVector ActorLocation = UpdatedComponent->GetComponentLocation();
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, ActorLocation + LookLocation);
	
	Orientation->SetRelativeRotation(Rotation);
}

void UMoveComponent::GroundCheck()
{
	FHitResult*  HitResult = new FHitResult();
	
	FVector UpVector = UpdatedComponent->GetUpVector();
	FVector ComponentLoc = UpdatedComponent->GetComponentLocation();
	float ColliderHalfHeight = Collider->GetScaledCapsuleHalfHeight();
	FVector FeetPos = ComponentLoc - (UpVector * ColliderHalfHeight) - 0.1f;
	FVector EndTrace = FeetPos - UpVector;
	
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	if(GetWorld()->LineTraceSingleByChannel(*HitResult, FeetPos, EndTrace, ECC_Visibility, *TraceParams)) bIsGrounded = true;

	else bIsGrounded = false;
}

void UMoveComponent::Jump()
{
	if(!bIsGrounded) return;

	GravitationalMovement += JumpStrength;
}

void UMoveComponent::TryMovePawn(float DeltaTime)
{

	//nullchecks
	if(!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime) || !Controller) return;
	
	//get input and directional vectors
	FVector Forward = Controller->GetForwardVector();
	FVector Right = Controller->GetRightVector();
	FVector Up = Controller->GetUpVector();
	FVector Input = Controller->GetMovementInput().GetClampedToMaxSize(1.0f);

	//Calculate desired movement
	FVector DesiredMovementThisFrame = ((Forward * Input.X) + (Right * Input.Y) + (Up * Input.Z)) * ActorSpeed;

	//add gravitational movement if enabled
	if(bUseGravity)
	{
		if(bIsGrounded && GravitationalMovement <= 0) GravitationalMovement = 0;
		else GravitationalMovement += Gravity * DeltaTime;

		DesiredMovementThisFrame.Z += GravitationalMovement;
	}
	
	if(!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		if(Hit.IsValidBlockingHit()) SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
	}
	
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

void UMoveComponent::SetCollider(UCapsuleComponent* _Collider)
{
	if (_Collider == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Collider sent in to SetCollider is null"));
		return;
	}
	Collider = _Collider;
}

void UMoveComponent::SetActorSpeed(float Speed) { ActorSpeed = Speed; }

void UMoveComponent::ToggleGravity(bool Toggle) { bUseGravity = Toggle;}

void UMoveComponent::SetOrientWithMovement(bool Toggle) { OrientWithMovement = Toggle; }

void UMoveComponent::SetGravity(float _Gravity){ Gravity = _Gravity; }


