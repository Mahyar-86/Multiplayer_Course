// Fill out your copyright notice in the Description page of Project Settings.

#include "MP_HealthPotion.h"

#include "Components/BoxComponent.h"
#include "Interfaces/MP_PlayerInteraction.h"

AMP_HealthPotion::AMP_HealthPotion()
{
	PrimaryActorTick.bCanEverTick = false;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	
	HealthPotionMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	HealthPotionMesh->SetupAttachment(RootComponent);
	
	HealthPotionCollision = CreateDefaultSubobject<UBoxComponent>("Collision");
	HealthPotionCollision->SetupAttachment(RootComponent);
}

void AMP_HealthPotion::BeginPlay()
{
	Super::BeginPlay();
}

void AMP_HealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMP_HealthPotion::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!HasAuthority()) return;

	if (OtherActor->Implements<UMP_PlayerInteraction>())
	{
		IMP_PlayerInteraction::Execute_GetHealthPotion(OtherActor, PotionEffect);
		
		Destroy();
	}
}
