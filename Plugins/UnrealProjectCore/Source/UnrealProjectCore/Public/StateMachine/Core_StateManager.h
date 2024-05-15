// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core_StateBase.h"
#include "Core_StateManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECTCORE_API UCore_StateManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCore_StateManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void InitializeStates();
	
	bool bCanTickState = false;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "State Machine")
	FString InitialState;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "State Machine")
	TMap<FString, TSubclassOf<UCore_StateBase>> AvailableStates;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "State Machine Debug")
	bool bDebug = false;

	UPROPERTY(BlueprintReadOnly)
	TArray<UCore_StateBase*> StateHistory;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "State Machine Debug", meta = (ClampMin = "0", ClampMax = "10", UIMin = "0", UIMax = "10"))
	int32 StateHistoryLength;
	UPROPERTY(BlueprintReadOnly)
	UCore_StateBase* CurrentState;

	UPROPERTY()
	TMap<FString, UCore_StateBase*> StateMap;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void SwitchStateByKey(FString StateKey);
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void InitStateManager();
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void RefreshCurrentState();
};
