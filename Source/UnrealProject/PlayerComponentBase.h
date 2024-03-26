// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerComponentBase.generated.h"


struct FMoveSettings;
class UControllerComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API UPlayerComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:
	FMoveSettings* GetMoveSettings();
	UControllerComponent* GetController();

};
