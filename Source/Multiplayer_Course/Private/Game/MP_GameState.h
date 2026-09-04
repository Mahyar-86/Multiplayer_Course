// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MP_GameState.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_COURSE_API AMP_GameState : public AGameState
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	void AddTeamMember(APlayerController* NewPlayerController);
	
	/**
	 * @return the number of team that the player is in it.
	 * If it does not in a team or not valid, returns 0. 
	 */
	UFUNCTION()
	int32 GetTeamOfPlayerController(APlayerController* PlayerController) const;

private:

	UPROPERTY(Replicated)
	TArray<APlayerController*> Team_1_PlayerControllers;

	UPROPERTY(Replicated)
	TArray<APlayerController*> Team_2_PlayerControllers;
};
