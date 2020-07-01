// Copyright @CloudStudio 2020

#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "particles/ParticleSystemComponent.h"

AProjectileBase::AProjectileBase()
{
 	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;

	ProjectileTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Trail"));
	ProjectileTrail->SetupAttachment(RootComponent);

	InitialLifeSpan = 3.0f;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(LaunchSound)) return;

	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

void AProjectileBase::OnHit(
	UPrimitiveComponent* HitComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	FVector NormalImpulse, 
	const FHitResult& Hit)
{
	if (!ensure(GetOwner() || HitParticle || HitSound || HitShake) ||(
		!OtherActor && OtherActor == this && OtherActor == GetOwner())) return;

	UGameplayStatics::ApplyDamage(OtherActor, Damage, GetOwner()->GetInstigatorController(), this, DamageType);
	UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), FRotator::ZeroRotator);
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(HitShake, 1.0f);
	Destroy();
}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}