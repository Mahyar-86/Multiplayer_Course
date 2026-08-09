// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MP_PlayerInteraction.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMP_PlayerInteraction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MULTIPLAYER_COURSE_API IMP_PlayerInteraction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	USkeletalMeshComponent* GetPlayerMesh() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GrantBladePower(float Power);
};
