// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControllablePawnMovement.h"
#include "PawnController.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "ControllablePawnBase.generated.h"

UENUM(BlueprintType)
enum Perspectives
{
	FPS     UMETA(DisplayName = "First person view"),
	TPS     UMETA(DisplayName = "Third person view"),
	TDW		UMETA(DisplayName = "Top down view"),
	SCW     UMETA(DisplayName = "Static Camera view"),
};

UCLASS()
class CONTROLLABEPAWN_API AControllablePawnBase : public APawn
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCapsuleComponent> Collider;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> PawnMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> OrientationParent;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPawnController> PawnController;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UControllablePawnMovement> PawnMovement;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> FPSCamTarget;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> TPSCamTarget;

	UPROPERTY(EditAnywhere, Category = "Debug", meta=(DisplayName="Do not send event about input, instead update by itself. Used to debug and test movement settings"))
	bool bDebugMovement = true;

	UPROPERTY(EditAnywhere, Category = "Debug", meta=(DisplayName="Allow upwards movement while debugging"))
	bool bDebugAllowUpwardsMovement = true;

	UPROPERTY(EditAnywhere, Category = "Debug", meta=(DisplayName="Allow jumping while debugging"))
	bool bDebugAllowJump = true;

	void RotateTowardsMovement(float DeltaTime, float RotationSpeed) const;
	void CalculateControllerDirectionVectors();

	UPROPERTY()
	USceneComponent* CamRotLRTarget;
	UPROPERTY()
	USceneComponent* CamRotUDTarget;

	Perspectives CurrentPerspective;

	// allowing rotations, mostly used for disabling rotations on different camera perspectives
	bool bAllowRotation;
public:
	
	// Sets default values for this pawn's properties
	AControllablePawnBase();

	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	//call this function to set pawn to jump
	UFUNCTION(BlueprintCallable)
	virtual void OnJumpInput();

	//call this function when wanting to set crouch
	UFUNCTION(BlueprintCallable)
	virtual void OnToggleCrouch(bool toggle);

	//call this function when wanting to set sprint
	UFUNCTION(BlueprintCallable)
	virtual void OnToggleSprint(bool toggle);

	//call this function when wanting to set rotation
	UFUNCTION(BlueprintCallable)
	virtual void OnRotationInput(FVector2D Input);

	//call this function when wanting to set movement
	UFUNCTION(BlueprintCallable)
	virtual void OnMovementInput(FVector Input);

	//call this function to set camera perspective
	UFUNCTION(BlueprintCallable)
	virtual void SetPerspective(Perspectives NewPerspective);

	UPawnController* GetPawnController();
	USceneComponent* GetTPCamTarget();
	USceneComponent* GetFPCamTarget();
};