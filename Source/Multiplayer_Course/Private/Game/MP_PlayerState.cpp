// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_PlayerState.h"

#include "Net/UnrealNetwork.h"
#include "Utilities/MP_Utilities.h"

AMP_PlayerState::AMP_PlayerState()
{
	SetNetUpdateFrequency(10);
}

void AMP_PlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, PickupNum)
}

void AMP_PlayerState::SetPickupNum(const int32 NewPickupNum)
{
	PickupNum = NewPickupNum;
	
	FOnPickedUpItems.Broadcast(PickupNum);
}

void AMP_PlayerState::OnRep_PickupNum(const int32 OldPickupNum) const
{
	const FString LogMessage = FString::Printf(TEXT("Pickup number changed from %d to %d."), OldPickupNum, PickupNum);
	UMP_Utilities::PrintNetworkLogMessage(LogMessage, this);
	
	FOnPickedUpItems.Broadcast(PickupNum);
}
