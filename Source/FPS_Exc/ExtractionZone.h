// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExtractionZone.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UDecalComponent;
class USoundBase;

UCLASS()
class FPS_EXC_API AExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExtractionZone();

	UPROPERTY(VisibleAnywhere, Category=Dimensions)
	FVector SizeVector;

protected:
	UPROPERTY(VisibleAnywhere, Category = Components)
	UBoxComponent* BoxCollider;

	//UPROPERTY(VisibleAnywhere, Category = Components)
	//UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UDecalComponent* DecalComponent;

	UPROPERTY(EditDefaultsOnly, Category = SoundEffects)
	USoundBase* ObjectiveMissingSound;

	UPROPERTY(EditDefaultsOnly, Category = SoundEffects)
	USoundBase* MissionCompleteSound;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapHandler(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
