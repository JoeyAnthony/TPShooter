// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

// Sets default values
AFPSAICharacter::AFPSAICharacter() : ResetRotationTime(4.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SenseComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComponent"));
}

// Called when the game starts or when spawned
void AFPSAICharacter::BeginPlay()
{
	Super::BeginPlay();
	OriginalRotation = GetActorRotation();

	SenseComponent->OnSeePawn.AddDynamic(this, &AFPSAICharacter::OnPawnSeen);
	SenseComponent->OnHearNoise.AddDynamic(this, &AFPSAICharacter::OnNoiseInRange);
}

void AFPSAICharacter::OnPawnSeen(APawn* SeenPawn)
{
	if (!SeenPawn)
		return;
	DrawDebugLine(GetWorld(), GetActorLocation(), SeenPawn->GetActorLocation(), FColor::Yellow, false, 10.f, (uint8)'\000', 2.f);

	//direction vector
	FVector Dir = SeenPawn->GetActorLocation() - GetActorLocation();
	Dir.Normalize();
	//rotate towards
	FRotator NewLookAt = FRotator(0.f, FRotationMatrix::MakeFromX(Dir).Rotator().Yaw, 0.f);
	SetActorRotation(NewLookAt);

	ResetTimer();
	
	return;
}

void AFPSAICharacter::OnNoiseInRange(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugLine(GetWorld(), GetActorLocation(), Location, FColor::Red, false, 10.f, (uint8)'\000', 2.f);

	//direction vector
	FVector Dir = Location - GetActorLocation();
	Dir.Normalize();
	//rotate towards
	FRotator NewLookAt = FRotator(0.f, FRotationMatrix::MakeFromX(Dir).Rotator().Yaw, 0.f);
	SetActorRotation(NewLookAt);

	ResetTimer();
}

void AFPSAICharacter::OnTimerFunc()
{
	SetActorRotation(OriginalRotation);
}

void AFPSAICharacter::ResetTimer()
{
	GetWorldTimerManager().SetTimer(ResetRotationTimerHandle, this, &AFPSAICharacter::OnTimerFunc, ResetRotationTime);
}

// Called every frame
void AFPSAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

