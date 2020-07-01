// Copyright @CloudStudio 2020

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()
	
public:
	APawnTurret();
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.0f;

	FTimerHandle FireRateTimerHandle;

	APawnTank* PlayerPawn;

	void CheckFireCondition();

protected:
	virtual void BeginPlay() override;
	virtual void HandleDestruction() override;
};