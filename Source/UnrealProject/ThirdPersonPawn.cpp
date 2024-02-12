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

	DirectionalComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DirectionalComponent"));
	DirectionalComponent->SetupAttachment(RootComponent);

	MoveComponent = CreateDefaultSubobject<UMoveComponent>(TEXT("MoveComponent"));
	MoveComponent->SetupAttachment(RootComponent);	

	CamControllerComponent = CreateDefaultSubobject<UCamControllerComponent>(TEXT("CamController"));
	CamControllerComponent->SetupAttachment(RootComponent);

	TPSCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	TPSCameraBoom->SetupAttachment(RootComponent);

	TPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPSCamera"));
	TPSCamera->SetupAttachment(TPSCameraBoom);

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	FPSCamera->SetupAttachment(PlayerMesh);

	
}

// Called when the game starts or when spawned
void AThirdPersonPawn::BeginPlay()
{
	Super::BeginPlay();

	//setup references for other components
	MoveComponent->Setup(this, PlayerMesh, DirectionalComponent);
	CamControllerComponent->Setup(TPSCameraBoom, DirectionalComponent, TPSCamera);

	SetPerspective(TPS);
	MoveComponent->SetActorSpeed(WalkSpeed);
}

void AThirdPersonPawn::SetRotationInputLR(float Value)
{
	CamControllerComponent->SetRotationInputLR(Value);
}

void AThirdPersonPawn::SetRotationInputUD(float Value)
{
	CamControllerComponent->SetRotationInputUD(Value);
}

void AThirdPersonPawn::SetControllerInputLR(float Value)
{
	if (!bCanMove) return;
	MoveComponent->SetControllerInputLR(Value);
}

void AThirdPersonPawn::SetControllerInputFB(float Value)
{
	if (!bCanMove) return;
	MoveComponent->SetControllerInputFB(Value);
}

void AThirdPersonPawn::SetControllerInputUD(float Value)
{
	if (!bCanMove) return;
	MoveComponent->SetControllerInputUD(Value);
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
		CamControllerComponent->SetCamera(FPSCamera);
		CamControllerComponent->SetRotatedComponent(FPSCamera);
		MoveComponent->OrientWithMovement = false;
		CamControllerComponent->bCanRotateLR = false;
		break;
	case TPS:
		TPSCamera->SetActive(true);
		CamControllerComponent->SetCamera(TPSCamera);
		CamControllerComponent->SetRotatedComponent(TPSCameraBoom);
		MoveComponent->OrientWithMovement = true;
		CamControllerComponent->bCanRotateLR = true;
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

