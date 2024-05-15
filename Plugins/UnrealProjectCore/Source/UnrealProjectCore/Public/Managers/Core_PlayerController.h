// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core_PlayerCameraManager.h"
#include "GameFramework/PlayerController.h"
#include "Movement/Core_ControlledPawn.h"
#include "Movement/Core_PawnController.h"
#include "Core_PlayerController.generated.h"

UCLASS()
class UNREALPROJECTCORE_API ACore_PlayerController : public APlayerController
{
	
	GENERATED_BODY()
	
	virtual void OnPossess(APawn* InPawn) override;
	ACore_PlayerController();

	virtual void SetupInputComponent() override;
	virtual void SpawnPlayerCameraManager() override;
	
	void MoveXAxis(float Value);
	void MoveYAxis(float Value);
	void MoveZAxis(float Value);
	void RotateZAxis(float Value);
	void RotateYAxis(float Value);
	void Jump();

	UPROPERTY()
	UCore_PawnController* Controller;
	UPROPERTY()
	ACore_ControlledPawn* PossessedPawn;
	UPROPERTY()
	ACore_PlayerCameraManager* CameraManager;
	
	UPROPERTY(EditAnywhere)
	FName MoveXAxisName;
	UPROPERTY(EditAnywhere)
	FName MoveYAxisName;
	UPROPERTY(EditAnywhere)
	FName MoveZAxisName;
	UPROPERTY(EditAnywhere)
	FName RotateYAxisName;
	UPROPERTY(EditAnywhere)
	FName RotateZAxisName;
	UPROPERTY(EditAnywhere)
	FName JumpKeyName;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<ACore_PlayerCameraManager> CustomPlayerCameraManager;

public:
	
	ACore_ControlledPawn* GetPossessedPawn() const;
	UCore_PawnController* GetPawnController() const;
	ACore_PlayerCameraManager* GetPlayerCameraManager() const;
	
};
