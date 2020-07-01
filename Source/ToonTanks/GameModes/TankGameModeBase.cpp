// Copyright @CloudStudio 2020

#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Get references and set variables
	TargetTurrets = GetTargetTurretsCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerReference = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart();
}

int32 ATankGameModeBase::GetTargetTurretsCount()
{
	// TSubclassOf<APawnTurret> ClassToFind;
	// ClassToFind = APawnTurret::StaticClass();
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);

	return TurretActors.Num();
}

// Check what type of Actor died, if Player, go to lose condition, if Turret, tally
void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	// If turret destroy player, show lose result
	if (DeadActor == PlayerTank)
	{
		PlayerTank->PawnDestroyed();
		HandleGameOver(false);

		if (!ensure(PlayerControllerReference)) return;

		PlayerControllerReference->SetPlayerEnabledState(false);
	}
	// If player has destroyed all turrets, show win result
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->PawnDestroyed();
		TargetTurrets--;

		if (TargetTurrets == 0)
		{
			HandleGameOver(true);
		}
	}
}

void ATankGameModeBase::HandleGameStart()
{
	GameStart();

	if (!ensure(PlayerControllerReference)) return;

	PlayerControllerReference->SetPlayerEnabledState(false);

	FTimerHandle PlayerEnablehandle;
	GetWorld()->GetTimerManager().SetTimer(
		PlayerEnablehandle, 
		FTimerDelegate::CreateUObject(PlayerControllerReference, &APlayerControllerBase::SetPlayerEnabledState, true), 
		StartDelay, 
		false);
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
}