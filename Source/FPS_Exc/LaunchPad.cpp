// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ALaunchPad::ALaunchPad(): LaunchForce(1500.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LaunchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchMesh"));
	LaunchMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = LaunchMesh;

	LaunchCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("LaunchCollider"));
	LaunchCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LaunchCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	LaunchCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);
	LaunchCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();
	
	LaunchCollider->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::LaunchOverlappingActor);
}

void ALaunchPad::LaunchOverlappingActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* CastedCharacter = Cast<ACharacter>(OtherActor);
	if (CastedCharacter) {
		FVector Direction = GetActorForwardVector();
		Direction.Z = 1.f;
		CastedCharacter->LaunchCharacter(Direction * LaunchForce, true, true);
	}
	else{
		if (OtherComp->IsSimulatingPhysics()) {
			FVector Direction = GetActorForwardVector();
			FVector FinalVelocity = OtherComp->GetPhysicsLinearVelocity();
			FinalVelocity.X += Direction.X * LaunchForce;
			FinalVelocity.Y += Direction.Y * LaunchForce;
			FinalVelocity.Z = LaunchForce;
			OtherComp->AddImpulse(FinalVelocity,NAME_None, true);
		}
	}
}

// Called every frame
void ALaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

