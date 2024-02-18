// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "MoveComponent.h"
#include "CamControllerComponent.h"
#include "ControllerComponent.h"
#include "ThirdPersonPawn.generated.h"

UENUM(BlueprintType)
enum Perspectives
{
  FPS     UMETA(DisplayName = "First person"),
  TPS      UMETA(DisplayName = "Third person"),
};
UCLASS()
class UNREALPROJECT_API AThirdPersonPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AThirdPersonPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
	USpringArmComponent* TPSCameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* TPSCameraParent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* TPSCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* FPSCamera;

	UPROPERTY(Instanced, EditDefaultsOnly)
	UMoveComponent* MoveComponent;

	UPROPERTY(Instanced, EditDefaultsOnly)
	UCamControllerComponent* CamControllerComponent;

	UControllerComponent* ControllerComponent;

	//sets value for left/right movement
	UFUNCTION(BlueprintCallable)
	void SetMovementInputLR(float Value);
	//sets value for forward/back movement
	UFUNCTION(BlueprintCallable)
	void SetMovementInputFB(float Value);
	//sets value for up/down movement
	UFUNCTION(BlueprintCallable)
	void SetMovementInputUD(float Value);

	//sets value for left/right rotation
	UFUNCTION(BlueprintCallable)
	void SetPitchInput(float Value);
	//sets value for up/down rotation
	UFUNCTION(BlueprintCallable)
	void SetYawInput(float Value);
	//toggles if the pawn can move or not
	UFUNCTION(BlueprintCallable)
	void ToggleMovement(bool Toggle);
	//sets value for how fast the actor moves
	UFUNCTION(BlueprintCallable)
	void SetActorSpeed(float Speed);

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
