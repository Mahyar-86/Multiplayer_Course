// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_GameState.h"

#include "Net/UnrealNetwork.h"

void AMP_GameState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, Team_1_PlayerControllers);
	DOREPLIFETIME(ThisClass, Team_2_PlayerControllers);
}

void AMP_GameState::AddTeamMember(APlayerController* NewPlayerController)
{
	if (Team_1_PlayerControllers.Num() <= Team_2_PlayerControllers.Num())
	{
		Team_1_PlayerControllers.Add(NewPlayerController);
	}
	else
	{
		Team_2_PlayerControllers.Add(NewPlayerController);
	}
}

int32 AMP_GameState::GetTeamOfPlayerController(APlayerController* PlayerController) const
{
	if (PlayerController == nullptr)
	{
		return 0;
	}
	
	if (Team_1_PlayerControllers.Contains(PlayerController))
	{
		return 1;
	}
	
	if (Team_2_PlayerControllers.Contains(PlayerController))
	{
		return 2;
	}

	return 0;
}
