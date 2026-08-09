// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MP_Utilities.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_COURSE_API UMP_Utilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void PrintActorLocalNetRole(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	static void PrintActorRemoteNetRole(AActor* Actor);
};
