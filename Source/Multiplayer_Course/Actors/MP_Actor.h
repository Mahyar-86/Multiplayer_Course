// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MP_Actor.generated.h"

UCLASS()
class MULTIPLAYER_COURSE_API AMP_Actor : public AActor
{
	GENERATED_BODY()

public:
	AMP_Actor();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(Client, Reliable)
	void Client_PrintSomething();
};
