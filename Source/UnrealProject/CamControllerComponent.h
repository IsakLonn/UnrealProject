// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ControllerComponent.h"
#include "PlayerComponentBase.h"
#include "CamControllerComponent.generated.h"



UCLASS()
class UNREALPROJECT_API UCamControllerComponent : public UPlayerComponentBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCamControllerComponent();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetComponentRotatedUD(USceneComponent* _ComponentRotatedUD);
	void SetComponentRotatedLR(USceneComponent* _ComponentRotatedLR);
	void SetController(UControllerComponent* _Controller);
	
protected:
	
	UPROPERTY(EditAnywhere, meta=(ClampMin="-89", ClampMax="-30"), Category = "Camera rotation settings")
	float CameraUDMinPitch = -89;
	UPROPERTY(EditAnywhere, meta=(ClampMin="30", ClampMax="89"), Category = "Camera rotation settings")
	float CameraUDMaxPitch = 89;
	
	UPROPERTY(EditAnywhere, Category = "Rotation settings")
	float YawSpeed = 1;
	UPROPERTY(EditAnywhere, Category = "Rotation settings")
	float PitchSpeed = 1;

private:

	//reference to component rotating up/down
	USceneComponent* ComponentRotatedUD;
	//reference to component rotating left/right
	USceneComponent* ComponentRotatedLR;
		
	//reference to the controller/inputs
	UControllerComponent* Controller;

	//rotates components/references up/down and left/right 
	void TryRotateComponents();
};
