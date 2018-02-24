// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AISensingCharacter.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState : uint8
{
	AIStateIdle = 0,
	AIStateSuspicius,
	AIStateAlerted
};

UCLASS()
class FPSGAME_API AAISensingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAISensingCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Sensing")
	UPawnSensingComponent* SensingComponent;

	UFUNCTION()
	void OnSeeEvent(APawn* Pawn);

	UFUNCTION()
	void OnHearEvent(APawn* PawnInstigator, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetOrientation();

	UPROPERTY(VisibleAnywhere, Category = "State")
	EAIState AIState = EAIState::AIStateIdle;

	void ChangeState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChanged(EAIState State);

	UPROPERTY(EditInstanceOnly, category = "AI")
	bool bPatrol;

	UPROPERTY(EditInstanceOnly, category= "AI", meta= (EditCondition = "bPatrol"))
	TArray<AActor*> Waypoints;

	void MoveToNextWaypoint();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	FRotator OriginalOrientation;
	FTimerHandle TimerHandle_ResetOrient;

	//current point where the ai is on it or moving to
	AActor* CurrentWaypoint;
	int CurrentWaypointIndex;

	bool HasReachedWaypoint();
};
