// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"
#include "FPS_ExcCharacter.h"
#include "FPS_ExcGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AExtractionZone::AExtractionZone():SizeVector(200.f)
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BoxCollider->SetBoxExtent(SizeVector);
	RootComponent = BoxCollider;

	//MeshComponent = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	//MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//MeshComponent->SetupAttachment(RootComponent);

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	DecalComponent->DecalSize = SizeVector;
	DecalComponent->SetupAttachment(RootComponent);


	//BoxCollider->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void AExtractionZone::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AExtractionZone::OverlapHandler);
}

void AExtractionZone::OverlapHandler(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult){
	AFPS_ExcCharacter* Char = Cast<AFPS_ExcCharacter>(OtherActor);
	if (!Char)
		return;

	//UE_LOG(LogTemp, Log, TEXT("Inside Extracion Zone!"));
	if (Char->bIsCarryingObjective) { //TODO: Might cause an optimization error
		
		AFPS_ExcGameMode* GM = Cast<AFPS_ExcGameMode>(GetWorld()->GetAuthGameMode());
		if (GM) {
			GM->CompleteMission(Char);
			UGameplayStatics::PlaySound2D(this, MissionCompleteSound);
		}
	}
	else {
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}
}

