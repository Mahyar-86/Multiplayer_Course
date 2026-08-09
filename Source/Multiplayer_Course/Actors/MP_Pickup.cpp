// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_Pickup.h"

#include "Components/CapsuleComponent.h"
#include "Interfaces/MP_PlayerInteraction.h"


AMP_Pickup::AMP_Pickup()
{
	PrimaryActorTick.bCanEverTick = false;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	PickupMesh->SetupAttachment(RootComponent);
	
	PickupCollision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	PickupCollision->SetupAttachment(RootComponent);
}

void AMP_Pickup::BeginPlay()
{
	Super::BeginPlay();
}

void AMP_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMP_Pickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (!HasAuthority()) return;

	if (OtherActor->Implements<UMP_PlayerInteraction>())
	{
		IMP_PlayerInteraction::Execute_PlusPickedUp(OtherActor);
		Destroy();
	}
}
