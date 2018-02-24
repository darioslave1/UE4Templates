// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPadActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystem;

UCLASS()
class FPSGAME_API ALaunchPadActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPadActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* LaunchPadMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	UParticleSystem* LaunchParticleEffect;
	
	UFUNCTION()
	void LaunchActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditInstanceOnly, Category = "Launch")
	float LaunchStrenght;

	UPROPERTY(EditInstanceOnly, Category = "Launch")
	float LaunchPitch;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
