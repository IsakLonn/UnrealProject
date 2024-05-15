// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core_PawnController.h"
#include "Core_PawnMovement.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "StateMachine/Core_StateManager.h"
#include "Core_ControlledPawn.generated.h"

UCLASS()
class UNREALPROJECTCORE_API ACore_ControlledPawn : public APawn
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCapsuleComponent> Collider;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> PawnMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> OrientationParent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCore_PawnMovement> PawnMovement;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCore_StateManager> StateManager;

public:
	
	// Sets default values for this pawn's properties
	ACore_ControlledPawn();
	virtual void BeginPlay() override;

	USceneComponent* GetOrientationParent() const;
	UCore_PawnMovement* GetMovementComponent() const;
	
};
