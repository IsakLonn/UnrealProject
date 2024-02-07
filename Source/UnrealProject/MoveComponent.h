// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MoveComponent.generated.h"

//
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, ToolTip = "component for moving a pawn, be sure to set its variables by calling its setup function") )
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
	//component for forward vector
	USceneComponent* Forward;
	//component for right vector
	USceneComponent* Right;
	//component for mesh, used for rotating
	USceneComponent* Orientation;

	//sets movement input left/right
	UFUNCTION(BlueprintCallable)
	void SetMovementInputLR(float Value);
	//sets movement input forward/backward
	UFUNCTION(BlueprintCallable)
	void SetMovementInputFB(float Value);

	//toggles if the mesh can rotate or not
	UFUNCTION(BlueprintCallable)
	void ToggleRotation(bool toggle);
	//toggles if the pawn can move or not
	UFUNCTION(BlueprintCallable)
	void ToggleMovement(bool toggle);

	//toggles if the pawn can move or not
	UFUNCTION(BlueprintCallable)
	void SetMovementSpeed(float speed);

	//makes the mesh look where it is moving
	UFUNCTION(BlueprintCallable)
	void OrientVisualsWithMovement();

	void TryMovePlayer(float DeltaTime);

	FVector MovementInput;
	FRotator VisualsDefaultRotation;

	bool bCanMove = true;
	bool bCanRotate = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement settings")
	float WalkSpeed = 10;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement settings")
	float SprintSpeed = 10;

	float currentSpeed;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//sets up variables to be used by this component
	UFUNCTION(BlueprintCallable)
	void Setup(APawn* _Pawn, USceneComponent* _Forward, USceneComponent* _Right, USceneComponent* _Orientation);
		
};
