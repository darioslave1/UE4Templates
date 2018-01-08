// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHoleAndRevelations.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABlackHoleAndRevelations::ABlackHoleAndRevelations()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBlackHoleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackHoleMEsh"));
	mBlackHoleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = mBlackHoleMesh;

	mOuterCollision = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereCollision"));
	mOuterCollision->SetSphereRadius(3000);
	mOuterCollision->SetupAttachment(mBlackHoleMesh);

	mInnerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereCollision"));
	mInnerCollision->SetupAttachment(mBlackHoleMesh);

	//bind collision event
	mInnerCollision->OnComponentBeginOverlap.AddDynamic(this, &ABlackHoleAndRevelations::OverlappingInnerSphere);

}

// Called when the game starts or when spawned
void ABlackHoleAndRevelations::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlackHoleAndRevelations::OverlappingInnerSphere(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, CatchEffect, OtherActor->GetActorLocation(), FRotator::ZeroRotator, true);

	OtherActor->Destroy();
	
}

// Called every frame
void ABlackHoleAndRevelations::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingComps;
	GetOverlappingComponents(OverlappingComps);

	for (UPrimitiveComponent* Comp : OverlappingComps)
	{
		if (Comp->IsSimulatingPhysics())
		{
			//only with simulated physics components!
			const float Radius = mOuterCollision->GetScaledSphereRadius();
			const float ForceStrenght = -2000;

			//spingiamo lontano dal centro dato la forza negativa, spinta costante e non 
			//in base alla distanza dal centro, con accelerazione 
			Comp->AddRadialForce(GetActorLocation(), Radius, ForceStrenght, ERadialImpulseFalloff::RIF_Constant, true);
		}
		
	}
}

