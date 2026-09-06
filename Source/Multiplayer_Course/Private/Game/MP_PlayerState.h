// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MP_PlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPickedUpItemsDelegate, int32);

/**
 * 
 */
UCLASS()
class MULTIPLAYER_COURSE_API AMP_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AMP_PlayerState();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	int32 GetPickupNum() const { return PickupNum; }
	
	void SetPickupNum(int32 NewPickupNum);
	
	UFUNCTION()
	void OnRep_PickupNum(int32 OldPickupNum) const;
	
	FOnPickedUpItemsDelegate FOnPickedUpItems;
	
private:
	UPROPERTY(ReplicatedUsing = "OnRep_PickupNum")
	int32 PickupNum = 0;
};
