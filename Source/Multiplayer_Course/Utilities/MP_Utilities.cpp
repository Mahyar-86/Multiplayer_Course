// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_Utilities.h"

void UMP_Utilities::PrintActorLocalNetRole(AActor* Actor)
{
	switch (Actor->GetLocalRole())
	{
	case ROLE_None:
		UE_LOG(LogTemp, Warning, TEXT("Actor %s has local role: ROLE_None"), *Actor->GetActorNameOrLabel());
		break;
	case ROLE_SimulatedProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor %s has local role: ROLE_SimulatedProxy"), *Actor->GetActorNameOrLabel());
		break;
	case ROLE_AutonomousProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor %s has local role: ROLE_AutonomousProxy"), *Actor->GetActorNameOrLabel());
		break;
	case ROLE_Authority:
		UE_LOG(LogTemp, Warning, TEXT("Actor %s has local role: ROLE_Authority"), *Actor->GetActorNameOrLabel());
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Actor %s does not have a valid local role"), *Actor->GetActorNameOrLabel());
		break;
	}
}

void UMP_Utilities::PrintActorRemoteNetRole(AActor* Actor)
{
	switch (Actor->GetRemoteRole())
	{
	case ROLE_None:
		UE_LOG(LogTemp, Warning, TEXT("Actor %s has remote role: ROLE_None"), *Actor->GetActorNameOrLabel());
		break;
	case ROLE_SimulatedProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor %s has remote role: ROLE_SimulatedProxy"), *Actor->GetActorNameOrLabel());
		break;
	case ROLE_AutonomousProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor %s has remote role: ROLE_AutonomousProxy"), *Actor->GetActorNameOrLabel());
		break;
	case ROLE_Authority:
		UE_LOG(LogTemp, Warning, TEXT("Actor %s has remote role: ROLE_Authority"), *Actor->GetActorNameOrLabel());
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Actor %s does not have a valid remote role"), *Actor->GetActorNameOrLabel());
		break;
	}
}
