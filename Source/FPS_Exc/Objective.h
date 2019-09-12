// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objective.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UParticleSystem;

UCLASS()
class FPS_EXC_API AObjective : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Objective)
	UParticleSystem* PickupEffect;
	
public:	
	// Sets default values for this actor's properties
	AObjective();

	UPROPERTY(VisibleAnywhere, Category = Objective)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Objective)
	USphereComponent* CollisionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayEffect();

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
