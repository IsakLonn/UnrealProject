// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "ControllerComponent.h"
#include "Math.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GroundCheck();
	
	CalculateGravity(DeltaTime);
	CalculateForce(DeltaTime);
	
	SimpleMove(DeltaTime);
	if(bUseGravity && bIsGrounded) SnapActorToGround();
	FinalMove(DeltaTime);
	
	if(OrientWithMovement) RotateTowardsMovement(DeltaTime, 10);
	
}

void UMoveComponent::RotateTowardsMovement(float DeltaTime, float RotationSpeed) const
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
	
	FVector Direction = (Forward * Input.X) + (Right * Input.Y);
	FVector ActorLocation = UpdatedComponent->GetComponentLocation();
	FRotator Target = UKismetMathLibrary::FindLookAtRotation(ActorLocation, ActorLocation + Direction);
	FRotator CalculatedRotation = FMath::RInterpTo(Orientation->GetComponentRotation(), Target, DeltaTime, RotationSpeed);
	
	Orientation->SetRelativeRotation(CalculatedRotation);
}

void UMoveComponent::GroundCheck()
{
	bIsGrounded = false;

	//get/calculate values for sweep
	
	float radius = Collider->GetScaledCapsuleRadius();
	FVector SweepLocation = GetActorFeetLocation() + Controller->GetUpVector() * ((radius) - 4);
	
	//setup collisions to ignore
	
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(UpdatedComponent->GetAttachmentRootActor());
	
	FCollisionShape Shape = FCollisionShape::MakeSphere(radius);

	FHitResult* Hit = new FHitResult();
	
	//cast the sweep and check for collisions
	if(GetWorld()->SweepSingleByChannel(*Hit, SweepLocation, SweepLocation, FQuat::Identity, ECC_WorldStatic, Shape, *TraceParams))
	{
		float Angle = AMath::Angle(Controller->GetUpVector(), Hit->Normal);
		bool WithinRange = AMath::WithinRange(Angle, 0, MaxSlopeAngle);
		if(WithinRange)
		{
			bIsGrounded = true;
		}
		
	}
}

void UMoveComponent::SnapActorToGround()
{
	//nullchecks
	if(UpdatedComponent == nullptr) return;
	
	FHitResult Hit;

	//get/calculate values for checks

	const FVector UpVector = UpdatedComponent->GetUpVector();
	const FVector StartTrace = UpdatedComponent->GetComponentLocation();
	const FVector EndTrace = GetActorFeetLocation() - UpVector * 1000;
	
	//setup collisions to ignore
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(UpdatedComponent->GetAttachmentRootActor());

	//cast check and snap actor to location
	if(GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
		SafeMoveUpdatedComponent(Hit.Location - UpdatedComponent->GetComponentLocation(), UpdatedComponent->GetComponentRotation(), true, Hit);

}

void UMoveComponent::CalculateGravity(float DeltaTime)
{
	if(!bUseGravity) GravitationalMovement = 0;
	else
	{
		if(bIsGrounded && GravitationalMovement <= 0) GravitationalMovement = 0;
		else GravitationalMovement += Gravity * DeltaTime;
	}
}

void UMoveComponent::CalculateForce(float DeltaTime)
{
	Force = FMath::Lerp(Force, FVector::Zero(),ForceDissipationPerFrame * DeltaTime);
}

void UMoveComponent::Jump()
{
	if(!bIsGrounded) return;

	GravitationalMovement += JumpStrength;
}

void UMoveComponent::AddForce(FVector Direction, float Strength)
{
	Force += Direction * Strength;
	Force = UKismetMathLibrary::ClampVectorSize(Force, 0, MaxAppliedForce);
}

void UMoveComponent::SimpleMove(float DeltaTime)
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

	if(!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;

		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
		if(Hit.IsValidBlockingHit()) SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
	}
}

void UMoveComponent::FinalMove(float DeltaTime)
{
	//nullchecks
	if(!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime) || !Controller) return;
	
	//get input 
	FVector Up = Controller->GetUpVector();
	
	//Calculate desired movement
	FVector DesiredMovementThisFrame = Up * GravitationalMovement;

	DesiredMovementThisFrame += Force;

	if(!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;

		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
		if(Hit.IsValidBlockingHit()) SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
	}
}

void UMoveComponent::SetOrientation(USceneComponent* NewOrientation)
{
	if (NewOrientation == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Orientation sent in to SetOrientation is null"));
		return;
	}
	Orientation = NewOrientation;
}

void UMoveComponent::SetController(UControllerComponent* NewController)
{
	if (NewController == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("ControllerComponent sent in to SetControllerComponent is null"));
		return;
	}

	Controller = NewController;
}

void UMoveComponent::SetCollider(UCapsuleComponent* NewCollider)
{
	if (NewCollider == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Collider sent in to SetCollider is null"));
		return;
	}
	Collider = NewCollider;
}

void UMoveComponent::SetActorSpeed(const float Speed) { ActorSpeed = Speed; }

void UMoveComponent::ToggleGravity(const bool Toggle) { bUseGravity = Toggle;}

void UMoveComponent::SetOrientWithMovement(const bool Toggle) { OrientWithMovement = Toggle; }

void UMoveComponent::SetGravity(const float NewGravity){ Gravity = NewGravity; }