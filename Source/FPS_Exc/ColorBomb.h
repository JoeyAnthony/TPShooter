// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColorBomb.generated.h"

class UStaticMeshComponent;
class UParticleSystem;

UCLASS()
class FPS_EXC_API AColorBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColorBomb();

protected:
	UPROPERTY(VisibleAnywhere, Category=ColorBomb)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = ColorBomb)
	float ExplosionRadius;

	UPROPERTY(EditDefaultsOnly, Category = ColorBomb)
	float ExplosionImpulse;

	UPROPERTY(EditDefaultsOnly, Category = ColorBomb)
	float ExplosionDelay;

	UPROPERTY(EditDefaultsOnly, Category = ColorBomb)
	UParticleSystem* ExplosionEffect;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Explode();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
