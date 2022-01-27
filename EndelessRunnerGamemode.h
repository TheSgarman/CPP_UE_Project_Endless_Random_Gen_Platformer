// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndelessRunnerGamemode.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERCPP_API AEndelessRunnerGamemode : public AGameModeBase

{
	GENERATED_BODY()

		AEndelessRunnerGamemode();

virtual void BeginPlay() override;

virtual void Tick(float DeltaTime) override;

UPROPERTY(EditAnywhere)
TSubclassOf<APawn>PlayerRecharge;

UPROPERTY(EditAnywhere)
TSubclassOf<APawn>PhyObject;

UPROPERTY(EditAnywhere)
TSubclassOf<APawn>PhyObject2;

UPROPERTY(EditAnywhere)
TSubclassOf<APawn>PhyObject3;

UPROPERTY(EditAnywhere)
float Spawn_X_Min;

UPROPERTY(EditAnywhere)
float Spawn_X_Max;

UPROPERTY(EditAnywhere)
float Spawn_Y_Min;

UPROPERTY(EditAnywhere)
float Spawn_Y_Max;

UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
float Spawn_Y;

UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
float Spawn_Z;


UPROPERTY(EditAnywhere)
float Spawn_Z_Min;

UPROPERTY(EditAnywhere)
float Spawn_Z_Max;

void SpawnPlayerRecharge();


};