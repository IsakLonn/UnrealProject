// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/Core_PawnMovement.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Utils/Core_Math.h"


void UCore_PawnMovement::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	GroundCheck();
	
	CalculateGravity(DeltaTime);
	CalculateForce(DeltaTime);
	
	SimpleMove(DeltaTime);
	if(Settings.bUseGravity && Settings.bIsGrounded) SnapActorToGround();
	FinalMove(DeltaTime);

	// reset input
	bJumpThisFrame = false;
	DirectionThisFrame = FVector::Zero();
	
}

void UCore_PawnMovement::BeginPlay()
{
	Super::BeginPlay();
	UpdatedComponent = GetOwner()->GetRootComponent();
}

void UCore_PawnMovement::GroundCheck()
{
	Settings.bIsGrounded = false;

	//get/calculate values for sweep
	
	float radius = Cast<UCapsuleComponent>(UpdatedComponent)->GetScaledCapsuleRadius();
	FVector SweepLocation = GetActorFeetLocation() + UpdatedComponent->GetUpVector() * ((radius) - 4);
	
	//setup collisions to ignore
	
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(UpdatedComponent->GetAttachmentRootActor());
	
	FCollisionShape Shape = FCollisionShape::MakeSphere(radius);

	FHitResult* Hit = new FHitResult();
	
	//cast the sweep and check for collisions
	if(GetWorld()->SweepSingleByChannel(*Hit, SweepLocation, SweepLocation, FQuat::Identity, ECC_WorldStatic, Shape, *TraceParams))
	{
		float Angle = UCore_Math::Angle(UpdatedComponent->GetUpVector(), Hit->Normal);
		bool WithinRange = UCore_Math::WithinRange(Angle, 0, Settings.MaxSlopeAngle);
		if(WithinRange) Settings.bIsGrounded = true;
		
	}
}

void UCore_PawnMovement::SnapActorToGround()
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

void UCore_PawnMovement::CalculateGravity(float DeltaTime)
{
	if(!Settings.bUseGravity) GravitationalMovement = 0;
	else
	{
		if(Settings.bIsGrounded && GravitationalMovement <= 0) GravitationalMovement = 0;
		else GravitationalMovement += Settings.Gravity * DeltaTime;
	}
}

void UCore_PawnMovement::AddForce(FVector Direction, float Strength)
{
	Force += Direction * Strength;
	Force = UKismetMathLibrary::ClampVectorSize(Force, 0, Settings.MaxAppliedForce);
}

void UCore_PawnMovement::AddMovement(FVector Direction)
{
	DirectionThisFrame = Direction;
}

void UCore_PawnMovement::Jump()
{
	bJumpThisFrame = true;
}

void UCore_PawnMovement::SetSettings(FMoveSettings NewSettings)
{
	Settings = NewSettings;
}

void UCore_PawnMovement::SimpleMove(float DeltaTime)
{
	
	//nullchecks
	if(!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) return;
	
	//Calculate desired movement
	FVector DesiredMovementThisFrame = DirectionThisFrame * Settings.ActorSpeed;

	if(!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
		if(Hit.IsValidBlockingHit()) SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
	}
}

void UCore_PawnMovement::FinalMove(float DeltaTime)
{
	//nullchecks
	if(!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) return;
	
	//check if jumping this frame
	if(bJumpThisFrame)
	{
		GravitationalMovement = Settings.ResetCurrentGravityOnJump ? 0 : GravitationalMovement;
		AddForce(UpdatedComponent->GetUpVector(), Settings.JumpStrength);
	}

	//Calculate desired movement
	FVector DesiredMovementThisFrame = UpdatedComponent->GetUpVector() * GravitationalMovement;

	DesiredMovementThisFrame += Force;

	if(!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;

		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
		if(Hit.IsValidBlockingHit()) SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
	}
}

void UCore_PawnMovement::CalculateForce(float DeltaTime) { Force = FMath::Lerp(Force, FVector::Zero(),Settings.ForceDissipationPerFrame * DeltaTime); }