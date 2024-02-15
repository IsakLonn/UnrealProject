// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonPawn.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AThirdPersonPawn::AThirdPersonPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = Collider;

	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(RootComponent);

	MoveComponent = CreateDefaultSubobject<UMoveComponent>(TEXT("MoveComponent"));
	MoveComponent->SetupAttachment(RootComponent);	

	CamControllerComponent = CreateDefaultSubobject<UCamControllerComponent>(TEXT("CamController"));
	CamControllerComponent->SetupAttachment(RootComponent);

	TPSCameraParent = CreateDefaultSubobject<USceneComponent>(TEXT("TPSCameraParent"));
	TPSCameraParent->SetupAttachment(RootComponent);
	
	TPSCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("TPSCameraBoom"));
	TPSCameraBoom->SetupAttachment(TPSCameraParent);

	TPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPSCamera"));
	TPSCamera->SetupAttachment(TPSCameraBoom);

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	FPSCamera->SetupAttachment(PlayerMesh);
	
}

// Called when the game starts or when spawned
void AThirdPersonPawn::BeginPlay()
{
	Super::BeginPlay();

	//create controller object
	if(ControllerComponent == nullptr)
	{
		ControllerComponent = NewObject<UControllerComponent>(this);
		check(ControllerComponent != nullptr)
		ControllerComponent->RegisterComponent();
	}

	//set cam controller references/settings
	CamControllerComponent->SetController(ControllerComponent);
	CamControllerComponent->SetComponentRotatedUD(TPSCameraBoom);
	CamControllerComponent->SetComponentRotatedLR(TPSCameraParent);

	//set move component references/settings
	MoveComponent->SetController(ControllerComponent);
	MoveComponent->SetPawn(this);
	MoveComponent->SetActorSpeed(WalkSpeed);
	
	SetPerspective(TPS);

}

void AThirdPersonPawn::SetMovementInputLR(float Value)
{
	
	if (!bCanMove) return;
	ControllerComponent->SetMovementInputY(Value);
}

void AThirdPersonPawn::SetMovementInputFB(float Value)
{
	if (!bCanMove) return;
	ControllerComponent->SetMovementInputX(Value);
}

void AThirdPersonPawn::SetMovementInputUD(float Value)
{
	if (!bCanMove) return;
	ControllerComponent->SetMovementInputZ(Value);
}

void AThirdPersonPawn::SetPitchInput(float Value)
{
	if(ControllerComponent == nullptr) return;
	ControllerComponent->SetPitchInput(Value);
}

void AThirdPersonPawn::SetYawInput(float Value)
{
	if(ControllerComponent == nullptr) return;
	ControllerComponent->SetYawInput(Value);
}

void AThirdPersonPawn::ToggleMovement(bool Toggle)
{
	bCanMove = Toggle;
}

void AThirdPersonPawn::SetActorSpeed(float Speed)
{
	MoveComponent->SetActorSpeed(Speed);
}

void AThirdPersonPawn::SetPerspective(Perspectives Perspective)
{
	currentPerspective = Perspective;
	FPSCamera->SetActive(false);
	TPSCamera->SetActive(false);
	switch (Perspective)
	{
	case FPS:
		FPSCamera->SetActive(true);
		//CamControllerComponent->SetRotatedComponent(FPSCamera);
		MoveComponent->OrientWithMovement = false;
		break;
	case TPS:
		TPSCamera->SetActive(true);
		//CamControllerComponent->SetRotatedComponent(TPSCameraBoom);
		MoveComponent->OrientWithMovement = true;
		break;
	default:
		break;
	}
}

// Called every frame
void AThirdPersonPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AThirdPersonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

