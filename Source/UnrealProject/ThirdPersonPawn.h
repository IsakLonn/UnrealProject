// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "MoveComponent.h"
#include "CamComponent.h"
#include "ThirdPersonPawn.generated.h"


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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void TryRotateCamera(float DeltaTime);

protected:
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCapsuleComponent* Collider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* PlayerMesh;

	UStaticMeshComponent* CameraForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USpringArmComponent* CameraParent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* Camera;

	UPROPERTY(Instanced, EditDefaultsOnly, BlueprintReadOnly)
	UMoveComponent* MoveComponent;

	UPROPERTY(Instanced, EditDefaultsOnly, BlueprintReadOnly)
	UCamComponent* CamComponent;
	
	UPROPERTY(EditAnywhere, meta=(ClampMin="-89", ClampMax="-30"), Category = "Camera rotation settings")
	float CameraUDMinPitch = -89;
	UPROPERTY(EditAnywhere, meta=(ClampMin="30", ClampMax="89"), Category = "Camera rotation settings")
	float CameraUDMaxPitch = 89;
	UPROPERTY(EditAnywhere, Category = "Camera Rotation settings")
	float CamRotSpeed = 1;

	
private:
	// vector for player rotation input
	FVector RotationInput;
};
