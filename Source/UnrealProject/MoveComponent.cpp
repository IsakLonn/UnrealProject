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
	RayCastGroundTick();
	TryMoveActor(DeltaTime);
	if(OrientWithMovement) OrientVisualsWithMovement();
}

void UMoveComponent::OrientVisualsWithMovement() const
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

void UMoveComponent::RayCastGroundTick()
{
	//reset bools before checks
	bIsGrounded = false;
	bOnSlope = false;

	TArray<AActor*> BoxCastOutActors;

	//get/calculate raycast direction
	FVector UpVector = UpdatedComponent->GetUpVector();
	FVector ActorLocation = UpdatedComponent->GetComponentLocation();
	float ColliderHalfHeight = Collider->GetScaledCapsuleHalfHeight();
	float ColliderRadius = Collider->GetScaledCapsuleRadius();
	FVector FeetPos = GetActorFeetLocation();
	FVector EndTrace = FeetPos - UpVector * 25;
	FVector RadiusHalfSize = {ColliderRadius, ColliderRadius, 2};

	//setup collisions to ignore
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(UpdatedComponent->GetAttachmentRootActor());
	
	//cast checks
	if(GetWorld()->LineTraceSingleByChannel(*GroundRayCast, ActorLocation, EndTrace, ECC_Visibility, *TraceParams))
	{
		
		auto Distance = FVector::Distance(GroundRayCast->Location, FeetPos);
		auto Angle = AMath::Angle(GroundRayCast->Normal, UpVector);

		UE_LOG(LogTemp, Warning, TEXT("The Distance value is: %f"), Distance);
		UE_LOG(LogTemp, Warning, TEXT("The Angle value is: %f"), Angle);
		
		if(AMath::WithinRange(Angle, 0.1f, MaxSlopeAngle)) bOnSlope = true;
		bIsGrounded = bOnSlope ? true : Distance < 1; // somehow sloped movement works with this
		

		//if debugging, show raycast
		if(ShowGroundRayCast) DrawDebugLine(GetWorld(), ActorLocation, GroundRayCast->Location, FColor(255,0,0), false, 0.1f);
		
		
	}
}

void UMoveComponent::Jump()
{
	if(!bIsGrounded) return;

	GravitationalMovement += JumpStrength;
}

void UMoveComponent::TryMoveActor(float DeltaTime)
{

	//nullchecks
	if(!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime) || !Controller) return;
	
	//get input and directional vectors
	FVector Forward = Controller->GetForwardVector();
	FVector Right = Controller->GetRightVector();
	FVector Up = Controller->GetUpVector();
	FVector Input = Controller->GetMovementInput().GetClampedToMaxSize(1.0f);
	
	//Calculate desired movement
	FVector DesiredMovementThisFrame = ((Forward * Input.X) + (Right * Input.Y) + (Up * Input.Z));

	if(bOnSlope) DesiredMovementThisFrame = UKismetMathLibrary::ProjectVectorOnToPlane(DesiredMovementThisFrame, GroundRayCast->Normal);

	DesiredMovementThisFrame *= ActorSpeed;
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
		
		if(Hit.IsValidBlockingHit())
		{
			
			SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
			
		}
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


