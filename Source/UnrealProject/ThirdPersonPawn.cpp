// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonPawn.h"

#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AThirdPersonPawn::AThirdPersonPawn()
{

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create root component
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = Collider;

	//create object rotated
	OrientationParent = CreateDefaultSubobject<USceneComponent>(TEXT("OrientationParent"));
	OrientationParent->SetupAttachment(RootComponent);

	//create skeleton mesh
	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(OrientationParent);

	//create third-person cam root, also object rotated left/right while in third-person
	TPSCamLRRot = CreateDefaultSubobject<USceneComponent>(TEXT("TPSCamLRRot"));
	TPSCamLRRot->SetupAttachment(RootComponent);

	//create third-person cam root, also object rotated up/down while in third-person
	TPSCamUDRot = CreateDefaultSubobject<USceneComponent>(TEXT("TPSCamUDRot"));
	TPSCamUDRot->SetupAttachment(TPSCamLRRot);

	//create third-person cam target
	TPSCamTarget = CreateDefaultSubobject<USceneComponent>(TEXT("TPSCamTarget"));
	TPSCamTarget->SetupAttachment(TPSCamUDRot);

	//create first-person cam target
	FPSCamTarget = CreateDefaultSubobject<USceneComponent>(TEXT("FPSCamTarget"));
	FPSCamTarget->SetupAttachment(OrientationParent);

	//set up custom components
	CamControllerComponent = CreateDefaultSubobject<UCamControllerComponent>(TEXT("CamController"));
	MoveComponent = CreateDefaultSubobject<UMoveComponent>(TEXT("MoveComponent"));
	MoveComponent->UpdatedComponent = RootComponent;
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

	//set move component references/settings
	MoveComponent->SetController(ControllerComponent);
	MoveComponent->SetOrientation(OrientationParent);
	MoveComponent->SetActorSpeed(WalkSpeed);
	MoveComponent->SetCollider(Collider);
	
	SetPerspective(TPS);
	
}

void AThirdPersonPawn::SetMovementInputLR(float Value)
{
	
	if (!bCanMove || !MoveComponent || (MoveComponent->UpdatedComponent != RootComponent)) return;
	ControllerComponent->SetMovementInputY(Value);
}

void AThirdPersonPawn::SetMovementInputFB(float Value)
{
	if (!bCanMove || !MoveComponent || (MoveComponent->UpdatedComponent != RootComponent)) return;
	ControllerComponent->SetMovementInputX(Value);
}

void AThirdPersonPawn::SetMovementInputUD(float Value)
{
	if (!bCanMove || !MoveComponent || (MoveComponent->UpdatedComponent != RootComponent)) return;
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

void AThirdPersonPawn::Jump()
{
	MoveComponent->Jump();
}

void AThirdPersonPawn::SetPerspective(Perspectives Perspective)
{
	auto t = UGameplayStatics::GetGameInstance(GetWorld());
	const auto CameraManager = Cast<UMyGameInstance>(t)->CameraManager();
	
	currentPerspective = Perspective;
	switch (Perspective)
	{
	case FPS:
		CamControllerComponent->SetComponentRotatedLR(OrientationParent);
		CameraManager->AttachToComponent(FPSCamTarget, 0);
		CamControllerComponent->SetComponentRotatedUD(FPSCamTarget);
		MoveComponent->SetOrientWithMovement(false);
		break;
	case TPS:
		CameraManager->AttachToComponent(TPSCamTarget, 300);
		CamControllerComponent->SetComponentRotatedLR(TPSCamLRRot);
		CamControllerComponent->SetComponentRotatedUD(TPSCamUDRot);
		MoveComponent->SetOrientWithMovement(true);
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

