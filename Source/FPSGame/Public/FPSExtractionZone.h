// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSExtractionZone.generated.h"

class UBoxComponent;
class USoundBase;

UCLASS()
class FPSGAME_API AFPSExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSExtractionZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, Category = "ExtractionCollision")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "ExtractionDecal")
	UDecalComponent* DecalComp;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ObjectNotFoundEffect;

	UFUNCTION()
	void ExtractActor(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
