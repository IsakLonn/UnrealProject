// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControllablePawnBase.h"
#include "CustomPlayerCameraManagerBase.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class CONTROLLABEPAWN_API ACustomPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<ACustomPlayerCameraManagerBase> CustomPlayerCameraManager;
	ACustomPlayerControllerBase();
	void MoveXAxis(float Value);
	void MoveYAxis(float Value);
	void MoveZAxis(float Value);
	void RotateZAxis(float Value);
	void RotateYAxis(float Value);
	void SetPerspective(Perspectives NewPerspective);
	virtual void BeginPlay() override;

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

	bool bBlockMovement = false;
	bool bBlockRotation = false;
	
};
