// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "ThirdPersonPawn.generated.h"

UENUM()
enum Direction
{
  FB     UMETA(DisplayName = "Forward/Backward"),
  LR      UMETA(DisplayName = "Left/Right"),
};

UCLASS()
class UNREALPROJECT_API AThirdPersonPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AThirdPersonPawn();
public:
	//sets rotation input left/right
	UFUNCTION(BlueprintCallable)
	void SetRotationInputLR(float Value);
	//sets rotation input up/down
	UFUNCTION(BlueprintCallable)
	void SetRotationInputUD(float Value);
	//sets movement input left/right
	UFUNCTION(BlueprintCallable)
	void SetMovementInputLR(float Value);
	//sets movement input forward/backward
	UFUNCTION(BlueprintCallable)
	void SetMovementInputFB(float Value);
	//makes the mesh look where it is moving
	UFUNCTION(BlueprintCallable)
	void OrientPlayerWithMovement();
	//toggle movement on/off
	UFUNCTION(BlueprintCallable)
	void ToggleMovement(bool toggle);
	//toggle movement on/off
	UFUNCTION(BlueprintCallable)
	void ToggleRotation(bool toggle);
	//sets the movement speed of the player
	UFUNCTION(BlueprintCallable)
	void SetMovementSpeed(float speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void TryMovePlayer(float DeltaTime);
	void TryRotateCamera(float DeltaTime);

protected:
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCapsuleComponent* Collider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USkeletalMeshComponent* PlayerMesh;

	UStaticMeshComponent* CameraForward;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* CameraParent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, meta=(ClampMin="-89", ClampMax="-30"), Category = "Camera rotation settings")
	float CameraUDMinPitch = -89;
	UPROPERTY(EditAnywhere, meta=(ClampMin="30", ClampMax="89"), Category = "Camera rotation settings")
	float CameraUDMaxPitch = 89;
	UPROPERTY(EditAnywhere, Category = "Camera Rotation settings")
	float CamRotSpeed = 1;

	UPROPERTY(EditAnywhere, Category = "Toggle settings")
	bool MovementEnabled = true;
	UPROPERTY(EditAnywhere, Category = "Toggle settings")
	bool RotationEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement settings")
	float WalkSpeed = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement settings")
	float RunSpeed = 1;

	
private:
	// vector for player rotation input
	FVector RotationInput;
	// vector for player movement input
	FVector MovementInput; 
	// used when rotating player, saves starting rotation of mesh
	FRotator PlayerMeshDefaultRotation;
	float CurrentMovementSpeed;
};
