// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/Core_IInputListener.h"
#include "Core_PawnController.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECTCORE_API UCore_PawnController : public UActorComponent
{
	GENERATED_BODY()

public:
	//calculates direction of movement through input and up/forward/right directions
	UCore_PawnController();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void AddListener(ICore_IInputListener* InputListener);
	void RemoveListener(ICore_IInputListener* InputListener);

	void SetUpVector(FVector Vector);
	void SetForwardVector(FVector Vector);
	void SetRightVector(FVector Vector);

	FVector GetForwardVector() const;
	FVector GetRightVector() const;
	FVector GetUpVector() const;

	void SetMovementInputX(float Value);
	void SetMovementInputY(float Value);
	void SetMovementInputZ(float Value);

	void SendJumpDelegate();
	
	void SetYawInput(float Value);
	void SetPitchInput(float Value);

protected:
	
	FVector2D RotationInput;
	FVector MovementInput;
	
	FVector Forward;
	FVector Right;
	FVector Up;

	UPROPERTY()
	TMap<UObject*, ICore_IInputListener*> DelegatedInput;
		
};
