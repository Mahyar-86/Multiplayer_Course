// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_GameMode.h"

#include "Utilities/MP_Utilities.h"

AMP_GameMode::AMP_GameMode()
{
	bDelayedStart = true;
}

void AMP_GameMode::StartMatch()
{
	Super::StartMatch();
	
	UMP_Utilities::PrintNetworkLogMessage("Start Match!", this, 5, FColor::Yellow);
}

void AMP_GameMode::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(StartMatchTimerHandle, this, &AMP_GameMode::OnStartMatchTimer, 5, false);
}

void AMP_GameMode::OnStartMatchTimer()
{
	StartMatch();
}
