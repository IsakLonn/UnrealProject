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

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SetPawn(APawn* _Pawn);
	void SetOrientation(USceneComponent* _Orientation);
	void SetController(UControllerComponent* _Controller);

	//makes the mesh look where it is moving	
	//sets value for actors speed
	void SetActorSpeed(float speed);

	bool OrientWithMovement = true;
	
protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;
	//root pawn
	APawn* Pawn;
	//component for mesh, used for rotating
	USceneComponent* Orientation;
	//controller with information about directions of movement
	UControllerComponent* Controller;

	//starting rotation for visuals/mesh
	FRotator VisualsDefaultRotation;

	void TryMovePawn(float DeltaTime);

	void OrientVisualsWithMovement();

	UPROPERTY(EditAnywhere, Category = "Movement settings")
	float ActorSpeed;
};
