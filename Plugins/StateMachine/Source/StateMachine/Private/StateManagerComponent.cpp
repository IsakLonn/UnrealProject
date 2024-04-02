// Fill out your copyright notice in the Description page of Project Settings.


#include "StateManagerComponent.h"

void UStateManagerComponent::SwitchStateByKey(FString StateKey)
{
	
	//search for state
	UStateBase* NewState = StateMap.FindRef(StateKey);
	
	//check if state exist
	if(NewState->IsValidLowLevel())
	{
		
		//simply set as current state if no prior state
		if(!CurrentState) CurrentState = NewState;
		else
		{
			
			//debug if trying to change to existing state which is not repeatable
			if(CurrentState->GetClass() == NewState->GetClass() && !CurrentState->bCanRepeat)
			{
				if(bDebug) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Failed switching to state " + NewState->StateDisplayname.GetPlainNameString() + ". It is not repeatable");
			}
			else
			{
				//push as new state and add old to history
				
				bCanTickState = false;

				CurrentState->OnExitState();

				StateHistory.Push(CurrentState);
				if(StateHistory.Num() == StateHistoryLength) StateHistory.RemoveAt(0);

				CurrentState = NewState;
			}
		}
		//call enter state on new state
		if(CurrentState)
		{
			
			CurrentState->OnEnterState(GetOwner());
			bCanTickState = true;
		}
	}
	//debug that state does not exist
	else GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "New State " + StateKey + " is invalid");
}

void UStateManagerComponent::InitStateManager() { SwitchStateByKey(InitialState); }

void UStateManagerComponent::InitializeStates()
{
	if(AvailableStates.Num() == 0) return;
	for (auto i = AvailableStates.CreateConstIterator(); i; ++i)
	{
		UStateBase* State = NewObject<UStateBase>(this, i->Value);
		StateMap.Add(i->Key, State);
	}
}

// Sets default values for this component's properties
UStateManagerComponent::UStateManagerComponent() { PrimaryComponentTick.bCanEverTick = true; }


// Called when the game starts
void UStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializeStates();
}


// Called every frame
void UStateManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(bCanTickState) CurrentState->TickState();
	 if(bDebug)
	 {
	 	if(CurrentState) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Current State is " + CurrentState->StateDisplayname.GetPlainNameString());
	 	for(auto i = 0; i< StateHistory.Num(); i++) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Previous state: " + StateHistory[i]->StateDisplayname.GetPlainNameString());
	 }
}

