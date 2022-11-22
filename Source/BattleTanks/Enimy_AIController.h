// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enimy_AIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API AEnimy_AIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* BTree;
	
};
