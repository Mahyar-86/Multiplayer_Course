// Fill out your copyright notice in the Description page of Project Settings.


#include "LanMenu.h"

#include "Components/Button.h"

void ULanMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	const FInputModeUIOnly InputMode;
	GetOwningPlayer()->SetInputMode(InputMode);
	GetOwningPlayer()->SetShowMouseCursor(true);
	
	HostButton->OnClicked.AddDynamic(this, &ULanMenu::JoinButtonClicked);
	JoinButton->OnClicked.AddDynamic(this, &ULanMenu::JoinButtonClicked);
}

void ULanMenu::HostButtonClicked()
{
	HandleInputMode(UIOnly);
}

void ULanMenu::JoinButtonClicked()
{
	HandleInputMode(GameOnly);
}

void ULanMenu::HandleInputMode(const EInputMode InputMode) const
{
	APlayerController* PlayerController = GetOwningPlayer();
	
	if (PlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("HandleInputMode: PlayerController is nullptr"));
		return;
	}
	
	bool ShowMouseCursor = false;
	
	switch (InputMode)
	{
	case GameOnly:
		PlayerController->SetInputMode(FInputModeGameOnly());
		ShowMouseCursor = false;
		break;
	case UIOnly:
		PlayerController->SetInputMode(FInputModeUIOnly());
		ShowMouseCursor = true;
		break;
	case GameAndUI:
		PlayerController->SetInputMode(FInputModeGameAndUI());
		ShowMouseCursor = true;
		break;
	}
	
	GetOwningPlayer()->SetShowMouseCursor(ShowMouseCursor);
}
