// Copyright @CloudStudio 2020

#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APawnTank::APawnTank()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void APawnTank::BeginPlay()
{
	Super::BeginPlay();

    PlayerControllerReference = Cast<APlayerController>(GetController());
    bAlive = true;
}

void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    Rotate();
    Move();

    if (!ensure(PlayerControllerReference)) return;

    PlayerControllerReference->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
    RotateTurret(TraceHitResult.ImpactPoint);
}

void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalculateMoveInput(float Value)
{
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotateInput(float Value)
{
    RotateDirection = FQuat(FRotator(0, Value * RotateSpeed * GetWorld()->DeltaTimeSeconds, 0));
}

void APawnTank::Move()
{
    AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
    AddActorLocalRotation(RotateDirection, true);
}

void APawnTank::HandleDestruction()
{
    Super::HandleDestruction();

    bAlive = false;

    // Hide Player and disable player movement
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

bool APawnTank::IsPlayerAlive()
{
    return bAlive;
}