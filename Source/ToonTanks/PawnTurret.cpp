// Copyright @CloudStudio 2020

#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

APawnTurret::APawnTurret()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
    
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, 
        &APawnTurret::CheckFireCondition, FireRate, true, false);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!ensure(PlayerPawn) || (PlayerPawn->GetActorLocation() - GetActorLocation()).Size() > FireRange) return;

    // if have a PlayerPawn in range then rotate the turret to follow
    RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
    if (!ensure(PlayerPawn)) return;

    // if player is in range then fire
    if ((PlayerPawn->GetActorLocation() - GetActorLocation()).Size() <= FireRange)
    {
        Fire();
    }
}

void APawnTurret::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}