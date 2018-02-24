// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::MissionComplete(APawn * InstigatorPawn, bool bMissionComplete)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		AActor* SpectatorCamera = nullptr;
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpectatorCameraClass, OutActors);
		if (OutActors.Num() > 0)
		{
			SpectatorCamera = OutActors[0];

			//change the camera view target
			APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
			if (PC)
			{
				PC->SetViewTargetWithBlend(SpectatorCamera, 2.f, EViewTargetBlendFunction::VTBlend_Linear);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Spectator class not found, please update the GameMode blueprint!"));
		}
	}


	OnMissionCompleted(InstigatorPawn, bMissionComplete);
}
