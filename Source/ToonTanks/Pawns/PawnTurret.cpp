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

    // if have a PlayerPawn in range and PlayerPawn is alive, then rotate the turret to follow
    if (!ensure(PlayerPawn) || !PlayerPawn->IsPlayerAlive() || 
        (PlayerPawn->GetActorLocation() - GetActorLocation()).Size() > FireRange) return;

    RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
    // if have a PlayerPawn and it is alive and in range, then fire
    if (!ensure(PlayerPawn) || !PlayerPawn->IsPlayerAlive()) return;

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