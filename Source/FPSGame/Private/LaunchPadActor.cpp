// Fill out your copyright notice in the Description page of Project Settings.

#include "LaunchPadActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALaunchPadActor::ALaunchPadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LaunchPadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaunchPadMesh"));
	RootComponent = LaunchPadMesh;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPadActor::LaunchActor);

	LaunchStrenght = 2000.f;
	LaunchPitch = 45.f;
}

// Called when the game starts or when spawned
void ALaunchPadActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALaunchPadActor::LaunchActor(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	FRotator Rot = LaunchPadMesh->GetComponentRotation() + FRotator(LaunchPitch, 0.f, 0.f);
	FVector Impulse(Rot.Vector() * LaunchStrenght);
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (Character)
	{
		Character->LaunchCharacter(Impulse, true, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchParticleEffect, Character->GetActorLocation());
	}
	else
	{
		if (OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulse(Impulse, NAME_None, true);
		}
	}
}

// Called every frame
void ALaunchPadActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

