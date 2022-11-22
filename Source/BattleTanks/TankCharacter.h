// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Particles/ParticleSystem.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "TankCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;

UCLASS()
class BATTLETANKS_API ATankCharacter : public ACharacter
{

	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankCharacter();
	//virtual ~ATankCharacter(){
	//	delete(SParticle);
	//	delete(AudioCmpTankMove);
	//	delete(AudioCmpTankStill);
	//	//AudioCmpTankStill->DestroyComponent();
	//}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	void SpawnParticleOnLowHealth();
	void PlayAudio();
	UFUNCTION(BlueprintCallable)
		void CrouchOnCover();
private:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"));
	USpringArmComponent* SpringArm;
	bool isHighHealth = true;
	UParticleSystemComponent* SParticle = nullptr;
	UAudioComponent* AudioCmpTankMove = nullptr ;
	UAudioComponent* AudioCmpTankStill = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"));
	float BaseHealth = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"));
	float MaxHealth = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour Tree", meta = (AllowPrivateAccess = "true"));
	UBehaviorTree* BTree;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Common", meta = (AllowPrivateAccess = "true"));
	bool isCrouched = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage_Effect_Particle", meta = (AllowPrivateAccess = "true"));
	UParticleSystem* Particle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage_Effect_Particle", meta = (AllowPrivateAccess = "true"));
	float DecreaseAmountInPercent=0.5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"));
	USoundWave* TankStillAudio;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"));
	USoundWave* TankMovingAudio;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"));
	USoundWave* TankDestroyed;
};
