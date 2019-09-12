// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FPS_ExcGameMode.h"
#include "FPS_ExcHUD.h"
#include "FPS_ExcCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Templates/SharedPointer.h"

AFPS_ExcGameMode::AFPS_ExcGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPS_ExcHUD::StaticClass();
}

void AFPS_ExcGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> ReturnedActors;
	UGameplayStatics::GetAllActorsOfClass(this, MissionCompleteViewActorClass, ReturnedActors);

	if (ReturnedActors.Num() > 0)
		MissionCompleteViewActorPosition = ReturnedActors[0];
}

void AFPS_ExcGameMode::CompleteMission(APawn * InstigatorPawn)
{
	if (InstigatorPawn) {
		InstigatorPawn->DisableInput(nullptr);

		APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
		if (PC){
			if(MissionCompleteViewActorPosition.IsValid())
				PC->SetViewTargetWithBlend(MissionCompleteViewActorPosition.Get());
		}
	}

	OnMissionCompleted(InstigatorPawn);


}

