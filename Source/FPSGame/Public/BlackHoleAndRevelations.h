// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHoleAndRevelations.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API ABlackHoleAndRevelations : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHoleAndRevelations();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Black Hole")
	UStaticMeshComponent* mBlackHoleMesh;

	UPROPERTY(VisibleAnywhere, Category = "Black Hole")
	USphereComponent* mOuterCollision;

	UPROPERTY(VisibleAnywhere, Category = "Black Hole")
	USphereComponent* mInnerCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Black Hole")
	UParticleSystem* CatchEffect;

	UFUNCTION()
	void OverlappingInnerSphere(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
