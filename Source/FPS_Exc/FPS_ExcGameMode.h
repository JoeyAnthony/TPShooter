
// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPS_ExcGameMode.generated.h"

UCLASS(minimalapi)
class AFPS_ExcGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPS_ExcGameMode();

	UPROPERTY(EditAnywhere, Category = SpectateView)
	TWeakObjectPtr<AActor> MissionCompleteViewActorPosition;

	UPROPERTY(EditDefaultsOnly, Category= SpectateView)
	TSubclassOf<AActor> MissionCompleteViewActorClass;

	void BeginPlay() override;

	void CompleteMission(APawn* InstigatorPawn);

	UFUNCTION(BlueprintImplementableEvent, Category=GameMode)
	void OnMissionCompleted(APawn* InstigatorPawn);

	
};



