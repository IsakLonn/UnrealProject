// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CamControllerComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, ToolTip = "component for rotating a camera, be sure to set its variables by calling its Setup/Set function/s") )
class UNREALPROJECT_API UCamControllerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCamControllerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, meta=(ClampMin="-89", ClampMax="-30"), Category = "Camera rotation settings")
	float CameraUDMinPitch = -89;
	UPROPERTY(EditAnywhere, meta=(ClampMin="30", ClampMax="89"), Category = "Camera rotation settings")
	float CameraUDMaxPitch = 89;
	UPROPERTY(EditAnywhere, Category = "Camera Rotation settings")
	float CamRotSpeed = 1;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//sets up references to be used by component
	//_RotatedComponent = component that will be rotated
	//_Camera = currently used camera
	//_DirectionalComponent = component used to get forward/right/up directions
	void Setup(USceneComponent* _RotatedComponent, USceneComponent* _DirectionalComponent, UCameraComponent* _Camera);

	//sets rotation input left/right
	UFUNCTION(BlueprintCallable)
	void SetRotationInputLR(float Value);
	//sets rotation input up/down
	UFUNCTION(BlueprintCallable)
	void SetRotationInputUD(float Value);

	void SetRotatedComponent(USceneComponent* _RotatedComponent);
	void SetDirectionalComponent(USceneComponent* _DirectionalComponent);
	void SetCamera(UCameraComponent* _Camera);

	bool bCanRotateLR = true;
	bool bCanRotateUD = true;

private:
	// vector for player rotation input
	FVector RotationInput;

	//reference to component rotating up/down
	USceneComponent* RotatedComponent;

	USceneComponent* DirectionalComponent;

	UCameraComponent* Camera;

	void TryRotateCamera(float DeltaTime);
};
