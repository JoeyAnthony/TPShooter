// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class FPS_EXC_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	UPROPERTY(VisibleAnywhere, Category=LaunchPad)
	UStaticMeshComponent* LaunchMesh;

	UPROPERTY(VisibleAnywhere, Category = LaunchPad)
	UBoxComponent* LaunchCollider;

	UPROPERTY(EditDefaultsOnly, Category = LaunchPad)
	float LaunchForce;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void LaunchOverlappingActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
