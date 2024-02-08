// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CamComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, ToolTip = "component for rotating a camera, be sure to set its variables by calling its setup function") )
class UNREALPROJECT_API UCamComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCamComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, meta=(ClampMin="-89", ClampMax="-30"), Category = "Camera rotation settings")
	float CameraUDMinPitch = -89;
	UPROPERTY(EditAnywhere, meta=(ClampMin="30", ClampMax="89"), Category = "Camera rotation settings")
	float CameraUDMaxPitch = 89;
	UPROPERTY(EditAnywhere, Category = "Camera Rotation settings")
	float CamRotSpeed = 1;

	//sets rotation input left/right
	UFUNCTION(BlueprintCallable)
	void SetRotationInputLR(float Value);
	//sets rotation input up/down
	UFUNCTION(BlueprintCallable)
	void SetRotationInputUD(float Value);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//sets up references to be used by component
	UFUNCTION(BlueprintCallable)
	void Setup(USceneComponent* _CamLR, USceneComponent* _CamUD);

private:
	// vector for player rotation input
	FVector RotationInput;

	//reference to component rotating left/right
	USceneComponent* CamLR;
	//reference to component rotating up/down
	USceneComponent* CamUD;

	void TryRotateCamera(float DeltaTime);
};
