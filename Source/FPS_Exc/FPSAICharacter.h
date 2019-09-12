// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAICharacter.generated.h"

class UPawnSensingComponent;

UCLASS()
class FPS_EXC_API AFPSAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAICharacter();

protected:
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPawnSensingComponent* SenseComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);
	UFUNCTION()
	void OnNoiseInRange(APawn* NoiseInstigator, const FVector& Location, float Volume);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
