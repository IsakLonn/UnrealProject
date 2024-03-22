// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorMovementInterface.h"
#include "Components/SceneComponent.h"
#include "ActorGroundMovementComponent.generated.h"


UCLASS()
class UNREALPROJECT_API UActorGroundMovementComponent : public UActorComponent, public IActorMovementInterface
{
public:
	virtual void MovementInput(UControllerComponent* Controller, FVector Input) override;
	virtual void JumpInput(UControllerComponent* Controller) override;
	virtual void CrouchInput(UControllerComponent Controller) override;

private:
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorGroundMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
