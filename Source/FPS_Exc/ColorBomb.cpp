// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorBomb.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AColorBomb::AColorBomb(): ExplosionRadius(500.f), ExplosionImpulse(5000.f), ExplosionDelay(2.f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void AColorBomb::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle Explosion_Timer;
	GetWorldTimerManager().SetTimer(Explosion_Timer, this, &AColorBomb::Explode, ExplosionDelay);
	
}

void AColorBomb::Explode()
{
	FVector ThisLocation = GetActorLocation();
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, ThisLocation);

	FCollisionObjectQueryParams params;
	//params.AddObjectTypesToQuery(ECC_WorldDynamic);
	params.AddObjectTypesToQuery(ECC_PhysicsBody);

	TArray<FOverlapResult> HitResults;
	GetWorld()->OverlapMultiByObjectType(HitResults, ThisLocation, FQuat::Identity, params, FCollisionShape::MakeSphere(ExplosionRadius));

	for (FOverlapResult result : HitResults) {
		UMaterialInstanceDynamic* Material = result.GetComponent()->CreateAndSetMaterialInstanceDynamic(0);

		Material->SetVectorParameterValue("DiffuseColor", FLinearColor::MakeRandomColor());
		Material->SetVectorParameterValue("MSR", FLinearColor::MakeRandomColor());

		FVector DirVector = result.GetActor()->GetActorLocation() - ThisLocation;
		result.GetComponent()->AddImpulseAtLocation(DirVector*ExplosionImpulse, ThisLocation);
	}

	Destroy();
}

// Called every frame
void AColorBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

