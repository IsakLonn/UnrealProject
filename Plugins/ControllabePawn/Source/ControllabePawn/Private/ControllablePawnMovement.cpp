// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllablePawnMovement.h"

#include "ControllablePawnBase.h"
#include "ControllablePawnMath.h"
#include "Kismet/KismetMathLibrary.h"

void UControllablePawnMovement::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	GroundCheck();
	
	CalculateGravity(DeltaTime);
	CalculateForce(DeltaTime);
	CalculateVelocity();
	
	SimpleMove(DeltaTime);
	if(Settings.bUseGravity && Settings.bIsGrounded) SnapActorToGround();
	FinalMove(DeltaTime);
}

void UControllablePawnMovement::BeginPlay()
{
	Super::BeginPlay();
	UpdatedComponent = GetOwner()->GetRootComponent();
}

void UControllablePawnMovement::CalculateVelocity()
{
	
	//get input and directional vectors
	FVector Forward = GetOwnerController()->GetForwardVector();
	FVector Right = GetOwnerController()->GetRightVector();
	FVector Up = GetOwnerController()->GetUpVector();
	FVector Input = GetOwnerController()->ConsumeMovementInput();

	//Get desired movement
	auto InputVelocity = ((Forward * Input.X) + (Right * Input.Y) + (Up * Input.Z));

	Velocity = FMath::Lerp(Velocity, InputVelocity, Settings.Friction);
	Velocity = Velocity.GetClampedToSize(-1, 1);
}

void UControllablePawnMovement::GroundCheck()
{
	Settings.bIsGrounded = false;

	//get/calculate values for sweep
	
	float radius = Cast<UCapsuleComponent>(UpdatedComponent)->GetScaledCapsuleRadius();
	FVector SweepLocation = GetActorFeetLocation() + GetOwnerController()->GetUpVector() * ((radius) - 4);
	
	//setup collisions to ignore
	
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(UpdatedComponent->GetAttachmentRootActor());
	
	FCollisionShape Shape = FCollisionShape::MakeSphere(radius);

	FHitResult* Hit = new FHitResult();
	
	//cast the sweep and check for collisions
	if(GetWorld()->SweepSingleByChannel(*Hit, SweepLocation, SweepLocation, FQuat::Identity, ECC_WorldStatic, Shape, *TraceParams))
	{
		float Angle = AControllablePawnMath::Angle(GetOwnerController()->GetUpVector(), Hit->Normal);
		bool WithinRange = AControllablePawnMath::WithinRange(Angle, 0, Settings.MaxSlopeAngle);
		if(WithinRange)
		{
			Settings.bIsGrounded = true;
		}
		
	}
}

void UControllablePawnMovement::SnapActorToGround()
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

void UControllablePawnMovement::CalculateGravity(float DeltaTime)
{
	if(!Settings.bUseGravity) GravitationalMovement = 0;
	else
	{
		if(Settings.bIsGrounded && GravitationalMovement <= 0) GravitationalMovement = 0;
		else GravitationalMovement += Settings.Gravity * DeltaTime;
	}
}

void UControllablePawnMovement::AddForce(FVector Direction, float Strength)
{
	Force += Direction * Strength;
	Force = UKismetMathLibrary::ClampVectorSize(Force, 0, Settings.MaxAppliedForce);
}

void UControllablePawnMovement::SimpleMove(float DeltaTime)
{
	//nullchecks
	if(!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) return;
	
	//Calculate desired movement
	FVector DesiredMovementThisFrame = Velocity * Settings.ActorSpeed;
	
	if(!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;

		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
		if(Hit.IsValidBlockingHit()) SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
	}
}

void UControllablePawnMovement::FinalMove(float DeltaTime)
{
	//nullchecks
	if(!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) return;
	
	FVector Up = GetOwnerController()->GetUpVector();
	
	//check if jumping this frame
	if(GetOwnerController()->ConsumeIsJumping())
	{
		GravitationalMovement = Settings.ResetCurrentGravityOnJump ? 0 : GravitationalMovement;
		AddForce(Up, Settings.JumpStrength);
	}

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

FMoveSettings* UControllablePawnMovement::GetSettings() { return &Settings; }

void UControllablePawnMovement::CalculateForce(float DeltaTime) { Force = FMath::Lerp(Force, FVector::Zero(),Settings.ForceDissipationPerFrame * DeltaTime); }

UPawnController* UControllablePawnMovement::GetOwnerController() const { return GetOwner()->GetComponentByClass<UPawnController>(); }
