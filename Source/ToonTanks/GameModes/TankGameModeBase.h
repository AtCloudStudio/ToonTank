// Copyright @CloudStudio 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APwanTurret;
class APawnTank;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

	void ActorDied(AActor* DeadActor);

private:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	APawnTank* PlayerTank;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Game Loop", meta = (AllowPrivateAccess = "true"))
	int32 StartDelay = 4;

	APlayerControllerBase* PlayerControllerReference;

	int32 TargetTurrets = 0;

	int32 GetTargetTurretsCount();
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);
};