// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MP_PickupCountWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class MULTIPLAYER_COURSE_API UMP_PickupCountWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetPickupCount(int32 NewPickupCount) const;
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_PickupCount;
};
