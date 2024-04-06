// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CONTROLLABEPAWN_API UPawnController : public UActorComponent
{
	GENERATED_BODY()

public:	

	void SetUpComponentReference(USceneComponent* Component);
	void SetForwardComponentReference(USceneComponent* Component);
	void SetRightComponentReference(USceneComponent* Component);

	FVector GetForwardVector() const;
	FVector GetRightVector() const;
	FVector GetUpVector() const;

	void SetMovementInputX(float Value);
	void SetMovementInputY(float Value);
	void SetMovementInputZ(float Value);
	void SetMovementInput(FVector Input);
	
	void SetYawInput(float Value);
	void SetPitchInput(float Value);
	void SetRotationInput(FVector2D Input);
	
	void SetIsJumping();

	FVector2D ConsumeRotationInput();
	FVector ConsumeMovementInput();
	bool ConsumeIsJumping();
	

protected:
	
	FVector2D RotationInput;
	FVector MovementInput;
	UPROPERTY()
	USceneComponent* ForwardComponent;
	UPROPERTY()
	USceneComponent* RightComponent;
	UPROPERTY()
	USceneComponent* UpComponent;

	bool IsJumping;
};
