// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LanMenu.generated.h"

class UButton;
class UEditableTextBox;

UENUM()
enum EInputMode
{
	GameOnly,
	UIOnly,
	GameAndUI
};

UCLASS()
class MULTIPLAYER_COURSE_API ULanMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UEditableTextBox> TextBox_IpAddress;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> HostButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> JoinButton;
	
	UFUNCTION()
	void HostButtonClicked();
	
	UFUNCTION()
	void JoinButtonClicked();
	
	void HandleInputMode(EInputMode InputMode) const;
};
