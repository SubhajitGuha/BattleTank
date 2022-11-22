// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enimy_AIController.h"
#include "TankCharacter.h"

// Sets default values
ATankCharacter::ATankCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *SkeletalMesh->GetName());
	//Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
		//SetRootComponent(ACharacter::GetMesh());
		
	//}
}

// Called when the game starts or when spawned
void ATankCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpawnParticleOnLowHealth();
	PlayAudio();
}

// Called every frame
void ATankCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (SParticle )
	{
		if(BaseHealth < (DecreaseAmountInPercent * MaxHealth))
			SParticle->SetVisibility(true);
		else if(SParticle->IsVisible())
			SParticle->SetVisibility(false);
	}
	if (AudioCmpTankStill )
	{
		if (GetVelocity().Length() > 0)
			AudioCmpTankStill->SetVolumeMultiplier(0.0f);
		else
			AudioCmpTankStill->SetVolumeMultiplier(1.0f);
	}
	if (AudioCmpTankMove) {
		if(GetVelocity().Length() > 0)
			AudioCmpTankMove->SetVolumeMultiplier(1.0f);
		else
			AudioCmpTankMove->SetVolumeMultiplier(0.0f);
	}
}

// Called to bind functionality to input
void ATankCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATankCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (BaseHealth == 0) {
		if (TankDestroyed)
			UGameplayStatics::PlaySoundAtLocation(GetWorld(),TankDestroyed, GetCapsuleComponent()->GetComponentLocation());
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	BaseHealth = FMath::Clamp(BaseHealth - DamageTaken, 0.f, MaxHealth);
	return BaseHealth;
}

void ATankCharacter::CrouchOnCover()
{
	Crouch();
	isCrouched = true;
	if (!BTree)
		return;
	auto controller = GetController();
	auto AiController = Cast<AEnimy_AIController>(controller);
	if (!AiController)
		return;
	UE_LOG(LogTemp, Warning, TEXT("ai controller"));
	AiController->RunBehaviorTree(BTree);
}

void ATankCharacter::SpawnParticleOnLowHealth() {
	if (!Particle)
		return;
		SParticle = UGameplayStatics::SpawnEmitterAttached(Particle, GetCapsuleComponent());
		SParticle->SetVisibility(false);
}

void ATankCharacter::PlayAudio()
{
	if (TankStillAudio && GetVelocity().Length()<=0)
	{
		AudioCmpTankStill = UGameplayStatics::SpawnSoundAttached(TankStillAudio, GetCapsuleComponent());
	}
	if (TankMovingAudio)
	{
			AudioCmpTankMove = UGameplayStatics::SpawnSoundAttached(TankMovingAudio, GetCapsuleComponent());
			AudioCmpTankMove->SetVolumeMultiplier(0.0);
	}
}