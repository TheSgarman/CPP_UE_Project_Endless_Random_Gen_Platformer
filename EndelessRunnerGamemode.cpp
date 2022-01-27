// Fill out your copyright notice in the Description page of Project Settings.


#include "EndelessRunnerGamemode.h"
#include "GameFramework/Actor.h"
#include "RunnerCharacter.h"

AEndelessRunnerGamemode::AEndelessRunnerGamemode() {
	PrimaryActorTick.bCanEverTick = true;
}

void AEndelessRunnerGamemode::BeginPlay() {
	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AEndelessRunnerGamemode::SpawnPlayerRecharge, FMath::RandRange(1, 2), true);




}

void AEndelessRunnerGamemode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}


void AEndelessRunnerGamemode::SpawnPlayerRecharge()
{
	


	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);
	float RandZ = FMath::RandRange(Spawn_Z_Min, Spawn_Z_Max);

	FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
	FRotator SpawnRotation2 = FRotator(RandX, RandY - FMath::RandRange(200, 500), RandZ - FMath::RandRange(200, 500));

	FRotator SpawnRotation3 = FRotator(RandX, RandY - FMath::RandRange(200, 500), RandZ - FMath::RandRange(200, 500));

	FVector SpawnPosition = FVector(RandX, Spawn_Y, RandZ);
	FVector SpawnPosition2 = FVector(RandX, Spawn_Y - FMath::RandRange(200, 500), Spawn_Z- FMath::RandRange(200, 500));
	FVector SpawnPosition3 = FVector(RandX, Spawn_Y - FMath::RandRange(0, 600), Spawn_Z - FMath::RandRange(100, 300));
	FVector SpawnPosition4 = FVector(RandX, Spawn_Y - FMath::RandRange(100, 300), Spawn_Z - FMath::RandRange(100, 300));
	FVector SpawnPosition5 = FVector(RandX, Spawn_Y - FMath::RandRange(120, 400), Spawn_Z - FMath::RandRange(100, 300));



	GetWorld()->SpawnActor(PlayerRecharge, &SpawnPosition, &SpawnRotation);
	GetWorld()->SpawnActor(PhyObject, &SpawnPosition2, &SpawnRotation);
	GetWorld()->SpawnActor(PhyObject2, &SpawnPosition3, &SpawnRotation);
	GetWorld()->SpawnActor(PhyObject3, &SpawnPosition3, &SpawnRotation);
	GetWorld()->SpawnActor(PhyObject, &SpawnPosition4, &SpawnRotation);
	GetWorld()->SpawnActor(PhyObject, &SpawnPosition5, &SpawnRotation);
	GetWorld()->SpawnActor(PhyObject, &SpawnPosition5, &SpawnRotation);
}

