// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "Projectile_Actor.h"

// Sets default values
AProjectile_Actor::AProjectile_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollision;
}

// Called when the game starts or when spawned
void AProjectile_Actor::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentHit.AddDynamic(this,&AProjectile_Actor::HitResult);
}

// Called every frame
void AProjectile_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile_Actor::HitResult(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FTimerHandle Handle;
	if (OtherActor != GetOwner() && OtherActor != this)
	{
		TArray<AActor*> Ignore;
		bool result = UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, Hit.ImpactPoint, RadiusOfBlast, UDamageType::StaticClass(),Ignore, this, nullptr, true);
		UE_LOG(LogTemp, Warning, TEXT("%d"), result);
		//if (result == false)
		//{
		//	FPointDamageEvent Dmg;
		//	OtherActor->TakeDamage(DamageAmount, Dmg, OtherActor->GetInstigatorController(), this);
		//}
		if(OtherComp && OtherComp->IsSimulatingPhysics())
			OtherComp->AddImpulseAtLocation(GetVelocity()*ImpulseStrength,Hit.Location);
		if (Particle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle,FTransform(FRotator(0),Hit.ImpactPoint));
		}
		if (ProjectileExplosion)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ProjectileExplosion, BoxCollision->GetComponentLocation());
		}
		GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([=]() {Destroy(); }), DelayTime, false);
	}
}