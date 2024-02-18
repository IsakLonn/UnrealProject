// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraManager::ACameraManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = root;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(root);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraBoom);

	auto world = GetWorld();
	if(world == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error getting world when setting up CameraManager"));
	}
    else
    {
    	auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    	if(playerController != nullptr)playerController->SetViewTarget(this);
    	UE_LOG(LogTemp, Warning, TEXT("The playerController value is %s"), ( playerController != nullptr ? TEXT("true") : TEXT("false") ));
    }
	
}

// Called when the game starts or when spawned
void ACameraManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(_FollowTarget->GetComponentLocation());
	SetActorRotation(_FollowTarget->GetComponentRotation());
}

void ACameraManager::FollowTarget(USceneComponent* target, float followDistance)
{
	_FollowTarget = target;
	CameraBoom->TargetArmLength = followDistance;
	
}

