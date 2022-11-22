// Fill out your copyright notice in the Description page of Project Settings.


#include "Enimy_AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnimy_AIController::BeginPlay() {
	Super::BeginPlay();
	if (BTree) {
		RunBehaviorTree(BTree);
		auto location = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), location);
	}
}
void AEnimy_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
