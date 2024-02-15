// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControllerComponent.h"
#include "Components/SceneComponent.h"
#include "MoveComponent.generated.h"

//
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, ToolTip = "component for moving a actor, be sure to set its variables by calling its Setup/Set function/s") )
class UNREALPROJECT_API UMoveComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//root pawn
	APawn* Pawn;
	//component for mesh, used for rotating
	USceneComponent* Orientation;
	//component for getting the direction to go in (up/forward/right)
	USceneComponent* DirectionalComponent;
	UControllerComponent* ControllerComponent;
	
	//current input from controller
	FVector ControllerInput;
	//starting rotation for visuals/mesh
	FRotator VisualsDefaultRotation;

	void TryMovePawn(float DeltaTime);

	void OrientVisualsWithMovement();

	UPROPERTY(EditAnywhere, Category = "Movement settings")
	float ActorSpeed;
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//sets up variables to be used by this component
	//_Pawn = which pawn it controls
	//_Orientation = "visuals/mesh" of the Actor
	//_DirectionalComponent = component used to get forward/right/up directions
	void Setup(APawn* _Pawn, USceneComponent* _Orientation, USceneComponent* _DirectionalComponent);
	void SetPawn(APawn* _Pawn);
	void SetOrientation(USceneComponent* _Orientation);
	void SetDirectionalComponent(USceneComponent* _DirectionalComponent);
	void SetControllerComponent(UControllerComponent* _ControllerComponent);
	
	//sets value for left/right movement
	void SetControllerInputLR(float Value);
	//sets value for forward/back movement
	void SetControllerInputFB(float Value);
	//sets value for up/down movement
	void SetControllerInputUD(float Value);
	//makes the mesh look where it is moving	
	//sets value for actors speed
	void SetActorSpeed(float speed);

	bool OrientWithMovement = true;
		
};
