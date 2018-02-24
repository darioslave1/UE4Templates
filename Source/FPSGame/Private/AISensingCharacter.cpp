// Fill out your copyright notice in the Description page of Project Settings.

#include "AISensingCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "FPSGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/Navigation/NavigationSystem.h"

// Sets default values
AAISensingCharacter::AAISensingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("SensingComponent");
	SensingComponent->bSeePawns = true;
	SensingComponent->bHearNoises = true;

	SensingComponent->OnSeePawn.AddDynamic(this, &AAISensingCharacter::OnSeeEvent);
	SensingComponent->OnHearNoise.AddDynamic(this, &AAISensingCharacter::OnHearEvent);

	OriginalOrientation = GetControlRotation();

	bPatrol = false;
	CurrentWaypointIndex = 0;
}

// Called when the game starts or when spawned
void AAISensingCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (bPatrol)
	{
		MoveToNextWaypoint();
	}
}

void AAISensingCharacter::OnSeeEvent(APawn * Pawn)
{
	if (Pawn)
	{
		DrawDebugSphere(GetWorld(), Pawn->GetActorLocation(), 60.f, 6, FColor::Yellow, false, 3.f);

		ChangeState(EAIState::AIStateAlerted);

		AFPSGameMode* MyGameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (MyGameMode)
		{
			MyGameMode->MissionComplete(Pawn, false);
		}
	}

	if (GetController())
	{
		GetController()->StopMovement();
	}
}

void AAISensingCharacter::OnHearEvent(APawn * PawnInstigator, const FVector & Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 60.f, 6, FColor::Blue, false, 3.f);

	ChangeState(EAIState::AIStateSuspicius);

	FVector Direction = Location - GetActorLocation();
	FRotator RotationToNoise = Direction.Rotation();
	RotationToNoise.Pitch = 0.f;
	RotationToNoise.Roll = 0.f;

	if (PawnInstigator)
	{
		
		SetActorRotation(RotationToNoise);
	}

	//start a timer to come back to original orientation
	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrient);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrient, this, &AAISensingCharacter::ResetOrientation, 5.f, false);

	if (GetController())
	{
		GetController()->StopMovement();
	}
	
}

void AAISensingCharacter::ResetOrientation()
{
	SetActorRotation(OriginalOrientation);

	ChangeState(EAIState::AIStateIdle);

	if (bPatrol)
	{
		MoveToNextWaypoint();
	}
	
}

void AAISensingCharacter::ChangeState(EAIState NewState)
{
	if (NewState != AIState)
	{
		AIState = NewState;
		OnStateChanged(AIState);
	}
}

void AAISensingCharacter::MoveToNextWaypoint()
{
	//check here for a resetOrientation
	if (HasReachedWaypoint())
	{
		CurrentWaypointIndex = (CurrentWaypointIndex + 1) % Waypoints.Num();
	}
	
	UNavigationSystem::SimpleMoveToActor(GetController(), Waypoints[CurrentWaypointIndex]);
}

// Called every frame
void AAISensingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPatrol)
	{
		if (HasReachedWaypoint())
		{
			MoveToNextWaypoint();
		}
	}
	

}

// Called to bind functionality to input
void AAISensingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AAISensingCharacter::HasReachedWaypoint()
{
	AActor* Waypoint = Waypoints[CurrentWaypointIndex];

	FVector Delta = GetActorLocation() - Waypoint->GetActorLocation();
	float Distance = Delta.Size2D();

	if (Distance < 50.f)
	{
		return true;
	}
	else
		return false;

}

