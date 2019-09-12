// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class FPS_EXC_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHole();

protected:
	UPROPERTY(VisibleAnywhere, Category = BlackHole)
	float GravitationalForce;

	UPROPERTY(VisibleAnywhere, Category=Components)
	USphereComponent* OverlapComponent;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* MeshComponent;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
