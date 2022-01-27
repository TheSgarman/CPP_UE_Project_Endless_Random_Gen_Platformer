// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter.h"
#include "Spikes.h"
#include "WallSpike.h"
#include "Engine.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/InputComponent.h"
#include "Components/PointLightComponent.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARunnerCharacter::ARunnerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Side View Camera"));

	SideViewCamera->bUsePawnControlRotation = false;


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	GetCharacterMovement()->AirControl = 0.8f;
	GetCharacterMovement()->JumpZVelocity = 900.0f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	tempPos = GetActorLocation();
	yPosition = tempPos.Y+400.0f;
	zPosition = tempPos.Z+400.0f;

	//Light
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);
	LightInt = 10000.0f;
	PointLight->SetIntensity(LightInt);


	bUnlit = false;
	Power = 100.0f;
	Power_Treshold = 1.0f;



}

// Called when the game starts or when spawned
void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARunnerCharacter::OnBeginOverlap);
	CanMove = true;
	
	if (Player_UI_Widget_Class != nullptr) {
		Player_UI_Widget = CreateWidget(GetWorld(), Player_UI_Widget_Class);
		Player_UI_Widget->AddToViewport();
	}

	
}

void ARunnerCharacter::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName(), false));
}

// Called every frame
void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	tempPos = GetActorLocation();
	tempPos.X -= 950.0f;
	tempPos.Z = zPosition;
	SideViewCamera->SetWorldLocation(tempPos);
	Power -= DeltaTime * Power_Treshold;
	LightInt -= DeltaTime * Power_Treshold;
	PointLight->SetIntensity(LightInt);

	if (Power <= 0)
	{
		PointLight->SetIntensity(0);
		if (!bUnlit)
		{
			bUnlit = true;
			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &ARunnerCharacter::RestartLevel, 2.0f, false);
		}
	}

}

// Called to bind functionality to input
void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARunnerCharacter::MoveRight);


}

void ARunnerCharacter::MoveRight(float value)
{
	if (CanMove)
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), value);

}



void ARunnerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr) {
		ASpikes* WallSpike = Cast<AWallSpike>(OtherActor);
		ASpikes* Spike = Cast<ASpikes>(OtherActor);

		if (WallSpike || Spike)
		{
			GetMesh()->Deactivate();
			GetMesh()->SetVisibility(false);

			CanMove = false;
			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &ARunnerCharacter::RestartLevel, 2.0f, false);
		}
	}
	if (OtherActor->ActorHasTag("Recharge")) {
		UE_LOG(LogTemp, Warning, TEXT("Collided with"));
		Power += 10.0f;
		LightInt += 1000.0f;
		if (Power > 100.0f)
			Power = 100.0f;


	}

	if (OtherActor->ActorHasTag("PhyObject")) {
		UE_LOG(LogTemp, Warning, TEXT("Collided with PhyObject"));
		TArray<FHitResult> OutHits;

		FVector MyLocation = GetActorLocation();


		FCollisionShape MyColSphere = FCollisionShape::MakeSphere(500.0f);


		//DrawDebugSphere(GetWorld(), MyLocation, MyColSphere.GetSphereRadius(), 50, FColor::Cyan, true);

		bool isHit = GetWorld()->SweepMultiByChannel(OutHits, GetActorLocation(), MyLocation, FQuat::Identity, ECC_WorldDynamic, MyColSphere);

		if (isHit)
		{


			for (auto& Hit : OutHits)
			{

				UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>((Hit.GetActor())->GetRootComponent());

				if (MeshComp) {

					MeshComp->AddRadialImpulse(MyLocation, 400.f, 20000.f, ERadialImpulseFalloff::RIF_Linear, true);
					//MeshComp->AddForce(GetActorLocation() * 100000 * MeshComp->GetMass());

				}

			}

		}
	}
}

