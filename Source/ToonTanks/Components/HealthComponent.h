// Copyright @CloudStudio 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class ATankGameModeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(
		AActor* DamagedActor, 
		float Damage, 
		const class UDamageType* DamageType, 
		class AController* InstigatedBy, 
		AActor* DamageCauser);

public:	
	UHealthComponent();

private:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float DefaultHealth = 100.0f;
	float Health = 0.0f;

	ATankGameModeBase* GameModeReference;
};