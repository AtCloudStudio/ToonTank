// Copyright @CloudStudio 2020

#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;
	GameModeReference = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!ensure(GetOwner())) return;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(
	AActor* DamagedActor, 
	float Damage, 
	const UDamageType* DamageType, 
	AController* InstigatedBy,
	AActor* DamageCauser)
{
	if (Damage == 0 || Health == 0) return;

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	if (Health <= 0)
	{
		if (!ensure(GameModeReference)) return;

		GameModeReference->ActorDied(GetOwner());
	}
}