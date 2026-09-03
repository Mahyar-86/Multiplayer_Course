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

void AMP_Actor::OnRep_Owner()
{
	Super::OnRep_Owner();
	
	Server_PrintSomething();
}

void AMP_Actor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		//Client_PrintSomething();
	}
}

void AMP_Actor::Client_PrintSomething_Implementation()
{
	UMP_Utilities::PrintNetworkLogMessage("This is Client Something.", this, 30);
}

void AMP_Actor::Server_PrintSomething_Implementation()
{
	UMP_Utilities::PrintNetworkLogMessage("This is Server Something.", this, 30);
}
