// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_PickupCountWidget.h"

#include "Components/TextBlock.h"

void UMP_PickupCountWidget::SetPickupCount(const int32 NewPickupCount) const
{
	Text_PickupCount->SetText(FText::AsNumber(NewPickupCount));
}
