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

void UMP_Utilities::PrintNetworkLogMessage(const FString& Message,const AActor* Actor,const float TimeToDisplay, const FColor& Color)
{
	if (!GEngine) return;
	
	FString FinalMessage;
	
	if (Actor)
	{
		FString HasAuthority = Actor->HasAuthority() ? "Yes" : "No";
		
		FString NetMode;
		
		switch (Actor->GetNetMode())
		{
		case NM_Standalone:
			NetMode = "Standalone";
			break;
		case NM_DedicatedServer:
			NetMode = "DedicatedServer";
			break;
		case NM_ListenServer:
			NetMode = "ListenServer";
			break;
		case NM_Client:
			NetMode = "Client";
			break;
		case NM_MAX:
			NetMode = "Max";
			break;
		}
		
		FinalMessage = FString::Printf(
			TEXT(
				"Actor Name: %s" "\n"
				"Actor Local Role: %s" "\n"
				"Actor Remote Role: %s" "\n"
				"Actor Has Authority: %s" "\n"
				"Actor NetMode: %s" "\n"
				"Message:" "\n"
				"%s"
				),
				*Actor->GetName(),
				*UEnum::GetValueAsString(Actor->GetLocalRole()),
				*UEnum::GetValueAsString(Actor->GetRemoteRole()),
				*HasAuthority,
				*NetMode,
				*Message
				);
	}
	else
	{
		FinalMessage = Message;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, Color, FinalMessage);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMessage);
}
