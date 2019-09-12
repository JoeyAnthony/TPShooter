// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/ActorComponent.h"


// Sets default values
ABlackHole::ABlackHole(): GravitationalForce(2000.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComponent;

	OverlapComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComponent"));
	OverlapComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);
	OverlapComponent->SetupAttachment(RootComponent);
	OverlapComponent->SetSphereRadius(500.f);

}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingComponents;
	OverlapComponent->GetOverlappingComponents(OverlappingComponents);

	for (UPrimitiveComponent* Result : OverlappingComponents) {

		if (Result && Result->IsSimulatingPhysics()) {
			FVector ThisLocation = GetActorLocation();
			FVector NewDirection = ThisLocation - Result->GetOwner()->GetActorLocation();
			Result->AddForceAtLocation(NewDirection * GravitationalForce, ThisLocation);
		}

	}
}

