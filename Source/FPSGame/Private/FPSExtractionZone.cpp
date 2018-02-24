// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CollisionBox->SetBoxExtent(FVector(200.f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::ExtractActor);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	DecalComp->SetupAttachment(CollisionBox);
	DecalComp->DecalSize = FVector(200.f);
}

// Called when the game starts or when spawned
void AFPSExtractionZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSExtractionZone::ExtractActor(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
	if (Character)
	{
		if (Character->bIsCarringObjectivePickup)
		{
			AFPSGameMode* MyGameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
			if (MyGameMode)
			{
				MyGameMode->MissionComplete(Character, true);
			}
		}
		else
		{
			UGameplayStatics::PlaySound2D(GetWorld(), ObjectNotFoundEffect);
		}

	}
}

// Called every frame
void AFPSExtractionZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

