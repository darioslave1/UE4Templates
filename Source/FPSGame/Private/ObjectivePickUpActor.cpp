// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectivePickUpActor.h"
#include "Particles/ParticleSystem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObjectivePickUpActor::AObjectivePickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpMesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpCollision"));
	CollisionSphere->SetupAttachment(MeshComponent);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void AObjectivePickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObjectivePickUpActor::PlayEffect()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickUpEffect, GetActorLocation());
}

void AObjectivePickUpActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	//check the Actor is the FPSCharacter
	AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
	if (Character)
	{
		Character->bIsCarringObjectivePickup = true;

		PlayEffect();

		Destroy();
	}
}

// Called every frame
void AObjectivePickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

