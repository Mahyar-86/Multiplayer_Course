// Fill out your copyright notice in the Description page of Project Settings.

#include "MP_Actor.h"

#include "Utilities/MP_Utilities.h"

AMP_Actor::AMP_Actor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bNetLoadOnClient = true;
	bReplicates = true;
	SetReplicatingMovement(true);
}

void AMP_Actor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		Client_PrintSomething();
	}
}

void AMP_Actor::Client_PrintSomething_Implementation()
{
	UMP_Utilities::PrintNetworkLogMessage("This is Something.", this, 30);
}
