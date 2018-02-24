// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectivePickUpActor.generated.h"

class UParticleSystem;
class USphereComponent;

UCLASS()
class FPSGAME_API AObjectivePickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectivePickUpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	UParticleSystem* PickUpEffect;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	USphereComponent* CollisionSphere;

	void PlayEffect();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
