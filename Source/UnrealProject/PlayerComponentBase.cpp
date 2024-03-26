// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponentBase.h"
#include "MoveComponent.h"

FMoveSettings* UPlayerComponentBase::GetMoveSettings() { return GetOwner()->GetComponentByClass<UMoveComponent>()->GetSettings(); }

UControllerComponent* UPlayerComponentBase::GetController() { return GetOwner()->GetComponentByClass<UControllerComponent>(); }

