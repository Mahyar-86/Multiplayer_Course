// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MP_Teleport.h"

#include "Components/BoxComponent.h"


AMP_Teleport::AMP_Teleport()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetupAttachment(RootComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);
}


void AMP_Teleport::BeginPlay()
{
	Super::BeginPlay();
}

void AMP_Teleport::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (HasAuthority())
	{
		GetWorld()->ServerTravel("LVL_Destination");
	}
}