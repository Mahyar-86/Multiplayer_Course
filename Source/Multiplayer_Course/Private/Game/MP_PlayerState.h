// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MP_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_COURSE_API AMP_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(ReplicatedUsing = "OnRep_PickupNum")
	int32 PickupNum = 0;
	
	UFUNCTION()
	void OnRep_PickupNum(int32 OldPickupNum) const;
};
