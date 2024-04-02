// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MoveComponent.h"
#include "CamControllerComponent.h"
#include "ControllerComponent.h"
#include "../Plugins/StateMachine/Source/StateMachine/Public/StateManagerComponent.h"
#include "PlayerPawn.generated.h"

UENUM(BlueprintType)
enum Perspectives
{
  FPS     UMETA(DisplayName = "First person"),
  TPS      UMETA(DisplayName = "Third person"),
};

DECLARE_MULTICAST_DELEGATE(EmptyDelegate)
DECLARE_MULTICAST_DELEGATE_OneParam(VectorDelegate, FVector);

UCLASS()
class UNREALPROJECT_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UControllerComponent* GetController();
	UStateManagerComponent* GetStateManager();
	UMoveComponent* GetMovement();

	EmptyDelegate JumpDelegate;
	VectorDelegate MovementInputDelegate;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCapsuleComponent* Collider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* PlayerMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* OrientationParent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* TPSCamUDRot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* TPSCamLRRot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* TPSCamTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* FPSCamTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMoveComponent* MoveComponent;

	UPROPERTY(Instanced, EditDefaultsOnly)
	UCamControllerComponent* CamControllerComponent;

	UPROPERTY()
	UControllerComponent* ControllerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStateManagerComponent* StateManager;

	//call this function when wanting to set movement
	UFUNCTION(BlueprintCallable)
	void OnMovementInput(FVector Input);

	//call this function when wanting to set rotation
	UFUNCTION(BlueprintCallable)
	void OnRotationInput(FVector2D Input);
	
	//toggles if the pawn can move or not
	UFUNCTION(BlueprintCallable)
	void ToggleMovement(bool Toggle);
	//sets value for how fast the actor moves
	UFUNCTION(BlueprintCallable)
	void SetActorSpeed(float Speed);

	UFUNCTION(BlueprintCallable)
	void Jump();

	UFUNCTION(BlueprintCallable)
	void SetPerspective(Perspectives Perspective);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement settings")
	float WalkSpeed = 10;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement settings")
	float SprintSpeed = 10;

	bool bCanMove = true;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<Perspectives> currentPerspective;

	

};
