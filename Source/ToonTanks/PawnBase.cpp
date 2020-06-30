// Copyright @CloudStudio 2020

#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ToonTanks/Actors/ProjectileBase.h"

APawnBase::APawnBase()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	//// Update TurretMesh rotation to face towards the LookAtTarget passed in from the child class
	//// 1. Get start rotaion
	//FVector StartRotation = TurretMesh->GetComponentLocation();
	//// 2. Get target rotation
	//FVector TargetRotaiton = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	//// 3. Find turret rotation to look at
	//FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(StartRotation, TargetRotaiton);
	//// 4. Rotate turret
	//TurretMesh->SetWorldRotation(TurretRotation);

	TurretMesh->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(
		TurretMesh->GetComponentLocation(),
		FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z)));
}

void APawnBase::Fire()
{
	if (!ProjectileClass) return;

	// Get ProjectileSpawnPoint Location && Rotation, then spawn Projectile class at Location towards Rotation
	AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(
		ProjectileClass, 
		ProjectileSpawnPoint->GetComponentLocation(), 
		ProjectileSpawnPoint->GetComponentRotation());
	TempProjectile->SetOwner(this);
}

void APawnBase::HandleDestruction()
{
	// Universal functionality ---
	// Play death effects particle, sound and camera shake

	// ... Then do unique child overrides
	// -- PawnTurret - Inform GameMode Turret died -> Then Destroy() self
	// -- PawnTank - Inform GameMode Player died -> Then Hide() all components && stop movement Input
}