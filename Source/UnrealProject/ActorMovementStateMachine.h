// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorGroundMovementComponent.h"
#include "ControllerComponent.h"
#include "Components/SceneComponent.h"
#include "ActorMovementStateMachine.generated.h"

UENUM(BlueprintType)
enum MovementType
{
	Jumping     UMETA(DisplayName = "Jumping/Falling"),
	Ground,
	Flying,
	Swimming
  };
UCLASS()
//Controller for delegating information about movement, such as pressing the jump key. Can be seen as a control center
class UNREALPROJECT_API UActorMovementStateMachine : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorMovementStateMachine();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void MovementInput(UControllerComponent* Controller, FVector Input);
	void JumpInput(UControllerComponent* Controller);

private:
	MovementType CurrentMovement;
	
	UPROPERTY()
	UActorGroundMovementComponent* GroundMovement;
	
};
